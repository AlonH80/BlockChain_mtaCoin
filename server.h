
#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "bitcoin.h"

typedef char BOOL;
typedef unsigned int UINT;
#define TRUE 1
#define FALSE 0
#define NUM_OF_MINERS 4

typedef struct _miner {
    pthread_t* minerThread;
    BOOL newBlockFlag;
} miner;

miner* miners;

Singly_Linked_List* blockList;

void programLoop();
void initialize_srv();
void createMiners();
void create_genesis_block;
BLOCK_T* head_block();

BLOCK_T* waitForNewBlock();
BOOL verifyBlock(BLOCK_T*);
void notifyMiners();
void appendNewBlock(BLOCK_T*);

#endif
