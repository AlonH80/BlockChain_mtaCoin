/* ======================================================== */
/*   utility.c				       						    */
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------

#include "../include/utility.h"
//---------------------------------------------------------------------------
//------------------------- Private Methods Prototypes ----------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//----------------------- Private Methods Implementations -------------------
//---------------------------------------------------------------------------
PRIVATE
Uint
get_current_time_stamp()
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
	new_block->difficulty = DIFFICULTY;
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
		new_block->hash = createHashFromBlock(new_block);
		return new_block;
}

PUBLIC
Uint 
createHash(char* data)
{
    return(crc32(0L, (unsigned char*)data, strlen((const char*)data)));
}

PUBLIC
int 
check_difficulty(Uint i_hash, int i_difficulty)
{
    Uint difficulty_max_hash_val = 1;
    
	difficulty_max_hash_val = difficulty_max_hash_val << (sizeof(Uint) * 8 - i_difficulty);
	difficulty_max_hash_val--;

	return i_hash <= difficulty_max_hash_val ? TRUE : FALSE;
}

PRIVATE
void 
appendToString(char* i_OrigString, char* i_PartToAppend)
{
    int partLen = strlen(i_PartToAppend);
    int origStringLen = strlen(i_OrigString);
    for (int i = 0; i < partLen; ++i)
	{
        i_OrigString[origStringLen + i] = i_PartToAppend[i];
    }
    i_OrigString[origStringLen + partLen] = '\0';
}

PRIVATE
void 
appendIntToString(char* i_OrigString, Uint i_Num)
{
    //pthread_mutex_lock(&mallocLock);
    char* intString = malloc(200 * sizeof(char));
    //pthread_mutex_unlock(&mallocLock);
    sprintf((char*)intString, "%x", i_Num);
    appendToString(i_OrigString, intString);
    //pthread_mutex_lock(&mallocLock);
    free(intString);
    //pthread_mutex_unlock(&mallocLock);
}

PUBLIC
char*
concatBlock(bitcoin_block_data* i_Block)
{
    Uint STRING_SIZE = 800;
    //pthread_mutex_lock(&mallocLock);
    char* concatedData = malloc(STRING_SIZE * sizeof(char));
    //pthread_mutex_unlock(&mallocLock);

    appendIntToString(concatedData, i_Block->height);
    appendIntToString(concatedData, i_Block->time_stamp);
    appendIntToString(concatedData, i_Block->prev_hash);
    appendIntToString(concatedData, i_Block->nonce);
    appendIntToString(concatedData, i_Block->relayed_by);
    return concatedData;
}

PUBLIC
Uint
createHashFromBlock(bitcoin_block_data* i_Block){
    char* concatedBlock = concatBlock(i_Block);
    Uint hashValue  = createHash(concatedBlock);
    //pthread_mutex_lock(&mallocLock);
    free(concatedBlock);
    //pthread_mutex_unlock(&mallocLock);
    return hashValue;
}

PUBLIC
EBoolType
verify_block(bitcoin_block_data* i_Block)
{
    pthread_mutex_lock(&get_block_lock);
    headBlockHeight = g_curr_srv_head->height;
    pthread_mutex_unlock(&get_block_lock);
    calculatedHash = createHashFromBlock(i_Block);
EBoolType answer = i_Block->height != headBlockHeight + 1 ?
		FALSE : i_Block->hash != calculatedHash?
		FALSE : TRUE;

	return answer;
}