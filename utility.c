/* ======================================================== */
/*   utility.c				       						    */
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <zlib.h>
#include <string.h>
#include "../include/utility.h"
#include "../include/definitions.h"
#include "../include/bitcoin.h"
//#include "bitcoin.c"

//---------------------------------------------------------------------------
//------------------------- Private Methods Prototypes ----------------------
//---------------------------------------------------------------------------
Uint
get_current_time_stamp(void);

//---------------------------------------------------------------------------
//----------------------- Private Methods Implementations -------------------
//---------------------------------------------------------------------------
PRIVATE
Uint
get_current_time_stamp(void)
{
	return (Uint)time(NULL);
}

//---------------------------------------------------------------------------
//----------------------- Public Methods Implementations --------------------
//---------------------------------------------------------------------------

// Function should also get the prev hash
PUBLIC
bitcoin_block_data*
initialize_new_block(bitcoin_block_data* i_head_block)
{
	bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
	new_block->height = i_head_block->height + 1;
	new_block->time_stamp = get_current_time_stamp();
	new_block->prev_hash = i_head_block->hash;
	new_block->nonce = PLACE_HOLDER_TILL_MINER_WILL_MINE;		// MINER responsibility
	new_block->relayed_by = PLACE_HOLDER_TILL_MINER_WILL_MINE;  // MINER responsibility
    new_block->hash = PLACE_HOLDER_TILL_MINER_WILL_MINE;		// MINER responsibility
    return new_block;
}

PUBLIC
bitcoin_block_data* 
createGenesis()
{
		bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
		new_block->height = GENESIS_VAL;
		new_block->time_stamp = get_current_time_stamp();
		new_block->prev_hash = GENESIS_VAL;
		new_block->difficulty = DIFFICULTY;
		new_block->nonce = GENESIS_VAL;
		new_block->relayed_by = GENESIS_VAL;
		new_block->hash = createHash(concatBlock(&new_block));
		return new_block;
}

PUBLIC
Uint 
createHash(unsigned char* data)
{
	return(crc32(0L, data, strlen(data)));
}

PUBLIC
int 
check_difficulty(Uint i_hash, int i_difficulty)
{
    Uint difficulty_max_hash_val = 1;
    
	difficulty_max_hash_val = difficulty_max_hash_val << (sizeof(i_hash) * 8 - i_difficulty);
	difficulty_max_hash_val--;

	return i_hash <= difficulty_max_hash_val ? TRUE : FALSE;
}

PRIVATE
void 
appendToString(char* i_OrigString, const char* i_PartToAppend)
{
    int partLen = strlen(i_PartToAppend);
    int origStringLen = strlen(i_OrigString);
    for (int i = 0; i < partLen; ++i)
	{
        i_OrigString[origStringLen + i] = i_PartToAppend[i];
    }
}

PRIVATE
void 
appendIntToString(char* i_OrigString, Uint i_Num)
{
    const char* intString = (char*)malloc(10);
    //itoa(i_Num, intString, 10);
    sprintf(intString, "%llu", i_Num);
    appendToString(i_OrigString, intString);
    free(intString);
}

PUBLIC
char* 
concatBlock(bitcoin_block_data* i_Block)
{
    Uint STRING_SIZE = 100;
    char* concatedData = (char*)malloc(STRING_SIZE);
    appendIntToString(concatedData, i_Block->height);
    appendIntToString(concatedData, i_Block->time_stamp);
    appendIntToString(concatedData, i_Block->prev_hash);
    appendIntToString(concatedData, i_Block->difficulty);
    appendIntToString(concatedData, i_Block->nonce);
    appendIntToString(concatedData, i_Block->relayed_by);

    return concatedData;
}

PUBLIC
EBoolType
verify_block(bitcoin_block_data* i_Block)
{
    calculatedHash = createHash(concatBlock(&i_Block));
EBoolType answer = i_Block->height != g_curr_srv_head ?
		FALSE : g_curr_srv_head->hash != calculatedHash?
		FALSE : TRUE;

	return answer;
}