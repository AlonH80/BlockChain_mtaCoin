
#include "../include/miner.h"
#define DEBUG 1
#define DEB if (DEBUG) {printf("func %s, line %d\n", __func__, __LINE__);}
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
            //sleep(0.2); // for debugging only
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
    BOOL isRelevant = i_Block == getCurrentBlockFromServer();
    return isRelevant;
}

void updateBlock(bitcoin_block_data* i_Block, int i_miner_id){
    i_Block->nonce = 1;
    i_Block->relayed_by = i_miner_id;
    i_Block->hash = createHashFromBlock(i_Block);
}

void mineBlock(bitcoin_block_data* i_Block){
    BOOL def = check_difficulty(i_Block->hash, DIFFICULTY);
    int currNonce = i_Block->nonce;
    while(!def){
        i_Block->nonce = ++currNonce;
        i_Block->time_stamp = get_current_time_stamp();
        i_Block->hash = createHashFromBlock(i_Block);
        def = check_difficulty(i_Block->hash, DIFFICULTY);
    }
}