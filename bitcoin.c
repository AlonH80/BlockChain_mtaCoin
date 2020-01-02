/* ======================================================== */
/*   bitcoin.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/bitcoin.h"

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------
PUBLIC
void
print_bitcoin_block_data(bitcoin_block_data* block_to_print)
{
	printf("height(%ld), ", block_to_print->height);
	printf("timestamp(%ld), ", block_to_print->time_stamp);
	printf("hash(%ld), ", block_to_print->hash);
	printf("prev_hash(%ld), ", block_to_print->prev_hash);
	printf("difficulty(%ld), ", block_to_print->difficulty);
	printf("nonce(%ld)", block_to_print->nonce);
}

PUBLIC
void 
release_bitcoin_block_data(pVoid block_to_release)
{
	free(((bitcoin_block_data*)block_to_release)->hash_value);
	free(((bitcoin_block_data*)block_to_release)->height);
	free(((bitcoin_block_data*)block_to_release)->total);
	free(((bitcoin_block_data*)block_to_release)->time);
	free(((bitcoin_block_data*)block_to_release)->received_time);
	free(((bitcoin_block_data*)block_to_release)->relayed_by);
	free(((bitcoin_block_data*)block_to_release)->prev_block);
}