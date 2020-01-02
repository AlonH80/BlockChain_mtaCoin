
#include "miner.h"

int miner_id = -1;
int nonce = 0;

void programLoop(int i_Miner_id){
    miner_id = i_Miner_id;
    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;
    BOOL blockIsRelevant = TRUE;

    while(1){
        currBlock = getCurrentBlockFromServer();
        while(verifyBlockIsRelevant(currBlock)){
            newBlock = createBlock(currBlock->height);
            manipulateNonce();
            updateTimestamp(newBlock);
            verifyBlock(newBlock, DIFFICULTY);
            sendBlockToServer(newBlock);
            //waitResponse();
        }
    }
}

bitcoin_block_data* getCurrentBlockFromServer(){
    return curr_srv_head;
}

BOOL verifyBlockIsRelevant(){
    return NULL;
}

void manipulateNonce(bitcoin_block_data* i_Block){
    ++nonce;
}

void updateTimestamp(bitcoin_block_data* i_Block){
    i_Block->timestamp = getTimeStamp();
}

bitcoin_block_data* createBlock(int i_Height, int i_prevHash){
    bitcoin_block_data* block = (bitcoin_block_data*)malloc(sizeof(bitcoin_block_data));
    block->timestamp = get_current_time_stamp();
    block->height = i_Height + 1;
    block->hash = 0;
    block->prev_hash = i_prevHash;
    block->difficulty = DIFFICULTY;
    block->nonce =nonce;
    block->relayed_by = miner_id;
    // do {
    //Uint crcHash = crc32b(create_message());
    //block->hash = crcHash
    // } while(!verifyDifficulty(block));
    return block;
}

BOOL sendBlockToServer(bitcoin_block_data* i_Block){
    put_block = i_Block;
    return TRUE;
}

//UINT getTimeStamp(){
//    return (UINT)time(NULL);
//}

BOOL verifyBlockIsRelevant(bitcoin_block_data* i_Block){
    return i_Block == getCurrentBlockFromServer();
}

//void waitResponse(){
//    //sem_wait();
//}

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