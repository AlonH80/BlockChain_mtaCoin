
#ifndef DUMMY_MINER_H
#define DUMMY_MINER_H

#include "bitcoin.h"
#include "miner.h"
#include "utility.h"

#define FALSE_FACTOR 1

void* programFalseLoop();
void falselyMineBlock(bitcoin_block_data* i_Block);

#endif
