
#include "dummy_miner.h"
#include "miner.h"

void programFalseLoop(){
    miner_id = NUM_OF_MINERS + 1;
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
            falselyMineBlock(newBlock);
            sendBlockToServer(newBlock);
            usleep(1000);
        }
    }
}

void falselyMineBlock(bitcoin_block_data* i_Block){
    i_Block->hash = createHash(i_Block) + FALSE_FACTOR;
}