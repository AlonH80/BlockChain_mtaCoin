
#include "miner.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "utility.h"
#include "bitcoin.h"

int miner_id = -1;
int nonce = 0;
pthread_mutex_t get_block_lock;
pthrea_mutex_t set_block_lock;

void programLoop(int i_Miner_id){
    programInit();

    miner_id = i_Miner_id;
    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;
    BOOL blockIsRelevant = TRUE;

    while(1){
        pthread_mutex_lock(&get_block_lock);
        currBlock = getCurrentBlockFromServer();
        pthread_mutex_unlock(&get_block_lock);

        while(verifyBlockIsRelevant(currBlock)){
            newBlock = initialize_new_block(currBlock);
            updateBlock(newBlock);
            mineBlock(newBlock);
            sendBlockToServer(newBlock);
            usleep(200); // for debugging only
        }
    }

    programDestroy();
}

bitcoin_block_data* getCurrentBlockFromServer(){
    return curr_srv_head;
}

BOOL verifyBlockIsRelevant(){
    return NULL;
}

BOOL sendBlockToServer(bitcoin_block_data* i_Block){
    pthread_mutex_lock(&set_block_lock);
    //<name of global var> = i_Block;
    pthread_mutex_unlock(&set_block_lock);
    return TRUE;
}

BOOL verifyBlockIsRelevant(bitcoin_block_data* i_Block){
    return i_Block == getCurrentBlockFromServer();
}

void updateBlock(bitcoin_block_data* i_Block){
    char* hashVal = NULL;
    i_Block->nonce = ++nonce;
    i_Block->relayed_by = miner_id;
    hashVal = concatBlock(i_Block);
    i_Block->hash = createHash(hashVal);
    free(hashVal);
}

BOOL mineBlock(bitcoin_block_data* i_Block){
    while(checkDifficulty(i_Block, DIFFICULTY)){
        i_Block->nonce = ++nonce;
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