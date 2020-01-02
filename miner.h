
#ifndef MTACOIN_MINER_H
#define MTACOIN_MINER_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utility.h"
#include "bitcoin.h"

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
BOOL verifyBlock(bitcoin_block_data*, int);
BOOL sendBlockToServer(bitcoin_block_data*);
void waitResponse();

//int getDifficulty();
//UINT getTimeStamp();

#endif
