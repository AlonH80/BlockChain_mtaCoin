/* ======================================================== */
/*   utility.c				       						    */
/* ======================================================== */
#include <zlib.h>
#include <string.h>

Uint GENESIS_VAL = 0;

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------


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
initialize_new_block(bitcoin_block_data* i_head block)
{
	bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
	new_block->height = i_head block->height + 1;
	new_block->time_stamp = get_current_time_stamp();
	new_block->prev_hash = i_head block->hash;
	new_block->nonce = 0; // MINER responsibility
	new_block->relayed_by = NULL; // MINER responsibility
    new_block->hash = 0; // MINER responsibility
    return new_block;

}

bitcoin_block_data* createGenesis(){
		bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
		new_block->height = GENESIS_VAL;
		new_block->time_stamp = get_current_time_stamp();
		new_block->prev_hash = GENESIS_VAL;
		new_block->difficulty = DIFFICULTY;
		new_block->nonce = GENESIS_VAL;
		new_block->relayed_by = GENESIS_VAL;
		new_block->hash = GENESIS_VAL; // createHash(get_current_time_stamp()) - was here before, what's better?
		return new_block;
}

Uint createHash(unsigned char* data){
	return(crc32(0L, data, strlen(data)));
}

int checkDifficulty(Uint i_Hash, int i_Difficulty){
    int i;
    Uint difficultyMask = 0;
    for (i = 0; i < i_Difficulty; ++i){
        // i = 0 -> 1 << 31
        // i = 1 -> 1 << 30
        // etc.
        difficultyMask |= 1 << (sizeof(Uint) - i - 1);
    }

	return (difficultyMask & i_Hash) == 0;
}

void appendToString(char* i_OrigString, const char* i_PartToAppend){
    int partLen = strlen(i_PartToAppend);
    int origStringLen = strlen(i_OrigString);
    for (int i = 0; i < partLen; ++i){
        i_OrigString[origStringLen + i] = partToAppend[i];
    }
}

void appendIntToString(char* i_OrigString, Uint i_Num){
    const char* intString = itoa(i_Num);
    appendToString(i_OrigString, intString);
}

char* concatBlock(bitcoin_block_data* i_Block){
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
