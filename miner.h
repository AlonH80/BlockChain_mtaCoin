
#ifndef MTACOIN_MINER_H
#define MTACOIN_MINER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "bitcoin.h"
#include "utility.h"
typedef char BOOL;
typedef unsigned int UINT;

void* programLoop();

bitcoin_block_data* getCurrentBlockFromServer();
BOOL verifyBlockIsRelevant(bitcoin_block_data*);
void manipulateNonce();
void updateTimestamp(bitcoin_block_data*);
bitcoin_block_data* createBlock(int, int);
void mineBlock(bitcoin_block_data*);
BOOL sendBlockToServer(bitcoin_block_data*);
void waitResponse();
void updateBlock(bitcoin_block_data* i_Block, int i_miner_id);
void programInit();
void programDestroy();

#endif
