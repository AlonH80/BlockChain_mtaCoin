/* ======================================================== */
/*   bitcoin.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <pthread.h>
#include "../include/bitcoin.h"

//---------------------------------------------------------------------------
//---------------------- Synchronization mechanisms -------------------------
//---------------------------------------------------------------------------

void programInit()
{
	pthread_mutex_init(&get_block_lock, NULL);
	pthread_mutex_init(&set_block_lock, NULL);
    pthread_mutex_init(&set_id, NULL);
	pthread_cond_init(&wait_start_mine, NULL);
	pthread_cond_init(&new_block_arrive, NULL);
}

void programDestroy()
{
	pthread_mutex_destroy(&get_block_lock);
	pthread_mutex_destroy(&set_block_lock);
	pthread_mutex_destroy(&set_id);
    pthread_cond_destroy(&wait_start_mine);
    pthread_cond_destroy(&new_block_arrive);
}
//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------



//run_server(); using pthread
// run 4 miners
// run 1 false_miner

PUBLIC
void
print_bitcoin_block_data(bitcoin_block_data* block_to_print)
{
	printf("height(%u), ", block_to_print->height);
	printf("timestamp(%u), ", block_to_print->time_stamp);
	printf("hash(%u), ", block_to_print->hash);
	printf("prev_hash(%u), ", block_to_print->prev_hash);
	printf("difficulty(%u), ", block_to_print->difficulty);
	printf("nonce(%u)", block_to_print->nonce);
}

PUBLIC
void 
release_bitcoin_block_data(pVoid block_to_release)
{
//	free(((bitcoin_block_data*)block_to_release)->hash);
//	free(((bitcoin_block_data*)block_to_release)->height);
//	free(((bitcoin_block_data*)block_to_release)->nonce);
//	free(((bitcoin_block_data*)block_to_release)->time_stamp);
//	free(((bitcoin_block_data*)block_to_release)->difficulty);
//	free(((bitcoin_block_data*)block_to_release)->relayed_by);
//	free(((bitcoin_block_data*)block_to_release)->prev_hash);
    free(block_to_release);
}
