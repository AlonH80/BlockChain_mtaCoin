
#include "server.h"

void programLoop(){
    BLOCK_T* newBlock = NULL;
    BOOL appendNewBlock;

    initialize_srv();
    while(1){
        newBlock = waitForNewBlock();
        appendNewBlock = verifyBlock(newBlock);
        if (appendNewBlock){
            notifyMiners();
            appendNewBlock(newBlock);
        }
        else{
            perror("Invalid block\n");
        }
    }
}

void initialize_srv(){
    createMiners(NUM_OF_MINERS);
    generateGenesisBlock();
    srand(time(NULL));
}

void createMiners(){
    int i;
    miners = (miner*)malloc(sizeof(miner) * NUM_OF_MINERS);
    for (i = 0; i < NUM_OF_MINERS; ++i){
        pthread_create(miners[i].minerThread, NULL, /*func*/ NULL, itoa(i));
        miners[i].newBlockFlag = FALSE;
    }
}

void create_genesis_block{
    blockList = initialize_Empty_List(sizeof(Singly_Linked_Node), release_bitcoin_block_data);
    BLOCK_T* genesisData = initialize_bitcoin_block_data();
    appendNewBlock(genesisData);
}

void notifyMiners(){
    for (i = 0; i < NUM_OF_MINERS; ++i){
        miners[i].newBlockFlag = TRUE;
    }
}

void appendNewBlock(BLOCK_T* newBlock){
    appendToList(blockList, newBlock);
}

BLOCK_T* waitForNewBlock(){

}

BOOL verifyBlock(BLOCK_T*){

}