
#include "miner.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "utility.h"
#include "bitcoin.h"

pthread_mutex_t get_block_lock;
pthrea_mutex_t set_block_lock;

void programLoop(int i_miner_id){
    programInit();

    int miner_id = i_miner_id;
    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;
    BOOL blockIsRelevant = TRUE;

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

    programDestroy();
}

bitcoin_block_data* getCurrentBlockFromServer(){
    pthread_mutex_lock(&get_block_lock);
    bitcoin_block_data* currBlock = curr_srv_head;
    pthread_mutex_unlock(&get_block_lock);
    return currBlock;
}

BOOL sendBlockToServer(bitcoin_block_data* i_Block){
    pthread_mutex_lock(&set_block_lock);
    //<name of global var> = i_Block;
    pthread_mutex_unlock(&set_block_lock);
    return TRUE;
}

BOOL verifyBlockIsRelevant(bitcoin_block_data* i_Block){
    pthread_mutex_lock(&get_block_lock);
    BOOL isRelevant = i_Block == getCurrentBlockFromServer();
    pthread_mutex_unlock(&get_block_lock);
    return isRelevant;
}

void updateBlock(bitcoin_block_data* i_block, int i_miner_id){
    char* hashVal = NULL;
    i_Block->nonce = 1;
    i_Block->relayed_by = i_miner_id;
    hashVal = concatBlock(i_block);
    i_Block->hash = createHash(hashVal);
    free(hashVal);
}

BOOL mineBlock(bitcoin_block_data* i_Block){
    while(checkDifficulty(i_Block, DIFFICULTY)){
        i_Block->nonce = ++(i_Block->nonce);
        i_Block->timestamp = get_current_time_stamp();
        i_Block->hash = createHash(i_Block);
    }
}

void programInit(){
    pthread_mutex_init(&get_block_lock, NULL);
    pthread_mutex_init(&set_block_lock, NULL);
}

void programDestroy(){
    pthread_mutex_destroy(&get_block_lock, NULL);
    pthread_mutex_destroy(&set_block_lock, NULL);
}

int main(int argc, char* argv[]){
    if (argc < 2){
        perror("Invalid arguments must enter miner ID in argv[1]\n");
        exit(1);
    }
    else{
        programLoop(atoi(argv[1]));
    }
    return 0;
}