
#include "../include/dummy_miner.h"

void* programFalseLoop(){
    int miner_id = NUM_OF_MINERS + 1;
    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;
    //BOOL blockIsRelevant = TRUE;

    while(1){
        currBlock = getCurrentBlockFromServer();

        while(verifyBlockIsRelevant(currBlock)){
            newBlock = initialize_new_block(currBlock);
            updateBlock(newBlock, miner_id);
            falselyMineBlock(newBlock);
            sendBlockToServer(newBlock);
            sleep(2);
        }
    }
    return NULL;
}

void falselyMineBlock(bitcoin_block_data* i_Block){
    i_Block->hash = createHashFromBlock(i_Block) + FALSE_FACTOR;
}