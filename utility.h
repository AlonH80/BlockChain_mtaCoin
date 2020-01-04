/* ======================================================== */
/*   utility.h				       						    */
/* ======================================================== */
#ifndef UTILITY_H
#define UTILITY_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//--------------------------- Bitcoin Defines -------------------------------
//---------------------------------------------------------------------------
#define DIFFICULTY 16
#define GENESIS_VAL 0
#define PLACE_HOLDER_TILL_MINER_WILL_MINE 0
#define NUM_OF_MINERS 4

Uint calculatedHash;

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
bitcoin_block_data* initialize_new_block(bitcoin_block_data* i_head block);
bitcoin_block_data* createGenesis();
Uint createHash(unsigned char* data);
int check_difficulty(Uint i_Hash, int i_Difficulty);
void appendToString(char* i_OrigString, const char* i_PartToAppend);
void appendIntToString(char* i_OrigString, Uint i_Num);
char* concatBlock(bitcoin_block_data* i_Block);
EBoolType verify_block(bitcoin_block_data* i_Block);

#endif // !UTILITY_H