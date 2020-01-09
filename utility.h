/* ======================================================== */
/*   utility.h				       						    */
/* ======================================================== */
#ifndef UTILITY_H
#define UTILITY_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "bitcoin.h"
#include "linked_list.h"
#include "definitions.h"

//---------------------------------------------------------------------------
//--------------------------- Bitcoin Defines -------------------------------
//---------------------------------------------------------------------------
#define DIFFICULTY 16
#define GENESIS_VAL 0
#define PLACE_HOLDER_TILL_MINER_WILL_MINE 0
#define NUM_OF_MINERS 4

Uint calculatedHash;
FILE* logFile;

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------

Uint get_current_time_stamp();
bitcoin_block_data* initialize_new_block(bitcoin_block_data* i_head_block);
bitcoin_block_data* createGenesis();
Uint createHash(unsigned char* data);
int check_difficulty(Uint i_Hash, int i_Difficulty);
void appendToString(unsigned char* i_OrigString, unsigned char* i_PartToAppend);
void appendIntToString(unsigned char* i_OrigString, Uint i_Num);
unsigned char* concatBlock(bitcoin_block_data* i_Block);
Uint createHashFromBlock(bitcoin_block_data* i_Block);
EBoolType verify_block(bitcoin_block_data* i_Block);
void logBit(char* msg);

#endif // !UTILITY_H