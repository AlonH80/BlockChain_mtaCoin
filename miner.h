
#ifndef MTACOIN_MINER_H
#define MTACOIN_MINER_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef char BOOL;
typedef unsigned int UINT;
#define TRUE 1
#define FALSE 0

typedef struct _mtacoin_block {
    int         height;        // Incrementeal ID of the block in the chain
    int         timestamp;    // Time of the mine in seconds since epoch
    unsigned int     hash;        // Current block hash value
    unsigned int     prev_hash;    // Hash value of the previous block
    int        difficulty;    // Amount of preceding zeros in the hash
    int         nonce;        // Incremental integer to change the hash value
    int         relayed_by;    // Miner ID
} BLOCK_T;

int miner_id = -1;

void programLoop();

BLOCK_T* getCurrentBlockFromServer();
BOOL verifyBlockIsRelevant();
void manipulateNonce(BLOCK_T*);
void updateTimestamp(BLOCK_T*);
BLOCK_T* createBlock(int, int, int);
BOOL verifyBlock(BLOCK_T*, int);
BOOL sendBlockToServer(BLOCK_T*);

int getDifficulty();
UINT getTimeStamp();

#endif
