
#ifndef MTACOIN_MINER_H
#define MTACOIN_MINER_H

typedef char BOOL;
typedef unsigned int UINT;
#define TRUE 1
#define FALSE 0

void programLoop();

bitcoin_block_data* getCurrentBlockFromServer();
BOOL verifyBlockIsRelevant(bitcoin_block_data*);
void manipulateNonce();
void updateTimestamp(bitcoin_block_data*);
bitcoin_block_data* createBlock(int, int);
BOOL mineBlock(bitcoin_block_data*);
BOOL sendBlockToServer(bitcoin_block_data*);
void waitResponse();
void updateBlock(bitcoin_block_data* i_Block, int i_miner_id);
void programInit();
void programDestroy();

#endif
