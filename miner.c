
#include "../include/miner.h"

int thread_id = 0;

void* programLoop(){
    pthread_mutex_lock(&set_id);
    int miner_id = ++thread_id;
    pthread_mutex_unlock(&set_id);
    //pthread_cond_wait(&wait_start_mine);

    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;

    while(1){
        currBlock = getCurrentBlockFromServer();

        while(verifyBlockIsRelevant(currBlock)){
            newBlock = initialize_new_block(currBlock);
            updateBlock(newBlock, miner_id);
            mineBlock(newBlock);
            sendBlockToServer(newBlock);
            usleep(200); // for debugging only
        }
    }
}

bitcoin_block_data* getCurrentBlockFromServer(){
    pthread_mutex_lock(&get_block_lock);
    bitcoin_block_data* currBlock = g_curr_srv_head;
    pthread_mutex_unlock(&get_block_lock);
    return currBlock;
}

BOOL sendBlockToServer(bitcoin_block_data* i_Block){
    pthread_mutex_lock(&set_block_lock);
    g_proposed_srv_head = i_Block;
    pthread_mutex_unlock(&set_block_lock);
    pthread_cond_broadcast(&new_block_arrive);
    return TRUE;
}

BOOL verifyBlockIsRelevant(bitcoin_block_data* i_Block){
    pthread_mutex_lock(&get_block_lock);
    BOOL isRelevant = i_Block == getCurrentBlockFromServer();
    pthread_mutex_unlock(&get_block_lock);
    return isRelevant;
}

void updateBlock(bitcoin_block_data* i_Block, int i_miner_id){
    unsigned char* hashVal = NULL;
    i_Block->nonce = 1;
    i_Block->relayed_by = i_miner_id;
    hashVal = concatBlock(i_Block);
    i_Block->hash = createHash(hashVal);
    free(hashVal);
}

void mineBlock(bitcoin_block_data* i_Block){
    while(!check_difficulty(i_Block->hash, DIFFICULTY)){
        i_Block->nonce = ++(i_Block->nonce);
        i_Block->time_stamp = get_current_time_stamp();
        i_Block->hash = createHashFromBlock(i_Block);;
    }
}