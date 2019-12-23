/* ======================================================== */
/*   bitcoin.h				       						    */
/* ======================================================== */
#ifndef BITCOIN_H
#define BITCOIN_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "linked_list.h"

//---------------------------------------------------------------------------
//---------------------- Bitcoin Block Data Defines -------------------------
//---------------------------------------------------------------------------
typedef enum _BITCOIN_FIELDS 
{    
	HASH,
	HEIGHT,
	TOTAL,
	TIME,
	RECEIVED_TIME,
	RELAYED_BY,
	PREV_BLOCK,
} EBITCOIN_FIELDS;

#define TOTAL_AMOUNT_OF_FIELDS_TO_PARSE 7
#define BAD_FIELD_INPUT -1

typedef struct _field_type_struct
{ 
	char *key; 
	int val; 
} field_type_struct;

//---------------------------------------------------------------------------
//---------------------- Bitcoin Block Data Structure -----------------------
//---------------------------------------------------------------------------
typedef struct _mtacoin_block {
    int         height;        // Incrementeal ID of the block in the chain
    int         timestamp;    // Time of the mine in seconds since epoch
    unsigned int     hash;        // Current block hash value
    unsigned int     prev_hash;    // Hash value of the previous block
    int        difficulty;    // Amount of preceding zeros in the hash
    int         nonce;        // Incremental integer to change the hash value
    int         relayed_by;    // Miner ID
} BLOCK_T;

typedef BLOCK_T bitcoin_block_data;

//---------------------------------------------------------------------------
//---------------------- Public Method Prototypes ---------------------------
//---------------------------------------------------------------------------
Singly_Linked_List*
load_bitcoin_db(char* bc_db_f_name);

void
print_bitcoin_block_data(bitcoin_block_data* block_to_print);

void 
release_bitcoin_block_data(pVoid block_to_release);

#endif // BITCOIN_H