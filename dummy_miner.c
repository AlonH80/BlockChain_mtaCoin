
#include "dummy_miner.h"
#include "miner.h"

void programFalseLoop(int i_Miner_id){
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
            falselyMineBlock(newBlock);
            sendBlockToServer(newBlock);
            usleep(1000);
        }
    }

    programDestroy();
}

void falselyMineBlock(bitcoin_block_data* i_Block){
    i_Block->hash = createHash(i_Block) + FALSE_FACTOR;
}

int main(int argc, char* argv[]){
    if (argc < 2){
        perror("Invalid arguments must enter miner ID in argv[1]\n");
        exit(1);
    }
    else{
        programFalseLoop(atoi(argv[1]));
    }
    return 0;
}