
#include "miner.h"

void programLoop(int i_Miner_id){
    miner_id = i_Miner_id;
    BLOCK_T* currBlock;
    BLOCK_T* newBlock;
    int difficulty;
    BOOL blockIsRelevant = TRUE;

    while(1){
        currBlock = getCurrentBlockFromServer();
        newBlock = createBlock();
        while(blockIsRelevant){
            manipulateNonce(newBlock);
            updateTimestamp(newBlock);
            difficulty = getDifficulty();
            verifyBlock(newBlock, difficulty);
            if(sendBlockToServer(newBlock)){
                blockIsRelevant = FALSE;
            }
            else{
                blockIsRelevant = verifyBlockIsRelevant();
            }
        }
    }
}

BLOCK_T* getCurrentBlockFromServer(){
    return NULL;
}

BOOL verifyBlockIsRelevant(){
    return NULL;
}

void manipulateNonce(BLOCK_T* i_Block){
    ++(i_Block->nonce);
}

void updateTimestamp(BLOCK_T* i_Block){
    i_Block->timestamp = getTimeStamp();
}

BLOCK_T* createBlock(int i_Height, int i_Hash, int i_Nonce){
    BLOCK_T* block = (BLOCK_T*)malloc(sizeof(BLOCK_T));
    block->timestamp = 0;
    block->height = i_Height;
    block->hash = 0;
    block->prev_hash = i_Hash;
    block->difficulty = 0;
    block->nonce =i_Nonce;
    block->relayed_by = miner_id;
}

BOOL sendBlockToServer(BLOCK_T* i_Block){
    return FALSE;
}

int getDifficulty(){
    return 16;
}

UINT getTimeStamp(){
    return (UINT)time(NULL);
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