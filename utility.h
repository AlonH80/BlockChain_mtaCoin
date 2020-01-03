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


//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
bitcoin_block_data* initialize_new_block(bitcoin_block_data i_head block);
bitcoin_block_data* createGenesis();
Uint createHash(unsigned char* data);
int checkDifficulty(Uint i_Hash, int i_Difficulty);
void appendToString(char* i_OrigString, const char* i_PartToAppend);
void appendIntToString(char* i_OrigString, Uint i_Num);
char* concatBlock(bitcoin_block_data* i_Block);
verifyBlock(bitcoin_block_data* i_Block);

#endif // !UTILITY_H