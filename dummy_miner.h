
#ifndef DUMMY_MINER_H
#define DUMMY_MINER_H

#include "bitcoin.h"
#include "miner.h"
#include "utility.h"

#define FALSE_FACTOR 1

void programFalseLoop(int i_Miner_id);
void falselyMineBlock(bitcoin_block_data* i_Block);

#endif
