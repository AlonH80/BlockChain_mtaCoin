/* ======================================================== */
/*   bitcoin.h				       						    */
/* ======================================================== */
#ifndef BITCOIN_H
#define BITCOIN_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "definitions.h"
#include "linked_list.h"

//---------------------------------------------------------------------------
//------------------------ Bitcoin Type Defines -----------------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//--------------------------- Bitcoin Defines -------------------------------
//---------------------------------------------------------------------------
#define DIFFICULTY 16

//---------------------------------------------------------------------------
//---------------------- Bitcoin Block Data Structure -----------------------
//---------------------------------------------------------------------------
typedef struct _bitcoin_block_data
{
	Uint height;
	Uint time_stamp;
	Uint hash;
	Uint prev_hash;
	Uint difficulty;
	Uint nonce;
	Uint relayed_by;
	
} bitcoin_block_data;

pthread_mutex_t get_block_lock;
pthread_mutex_t set_block_lock;
pthread_mutex_t set_id;
pthread_cond_t wait_start_mine;
pthread_cond_t new_block_arrive;

bitcoin_block_data* g_curr_srv_head;
bitcoin_block_data* g_proposed_srv_head;

//---------------------------------------------------------------------------
//---------------------- Public Method Prototypes ---------------------------
//---------------------------------------------------------------------------
void
print_bitcoin_block_data(bitcoin_block_data* block_to_print);

void 
release_bitcoin_block_data(pVoid block_to_release);

#endif // !BITCOIN_H