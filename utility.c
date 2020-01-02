/* ======================================================== */
/*   utility.c				       						    */
/* ======================================================== */

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

PRIVATE
Uint
generate_random_positive_integer(void)
{
	//Initialization was called by the server, on it's power on (srand(time(NULL));),
	return rand() % 100000; //generate random numbers from 0 to 100,000	
}

//---------------------------------------------------------------------------
//----------------------- Public Methods Implementations --------------------
//---------------------------------------------------------------------------

// Function should also get the prev hash
PUBLIC
bitcoin_block_data*
initialize_new_block(bitcoin_block_data i_head block)
{
	//  bool isValidBlock = false 
	//	first define SIZE
	//  second define difficulty
	//  usnigned char concateData[SIZE]
	//	unsgined chat temp[SIZE]
	bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
	// while(!isValidBlock)
	//{
	new_block->height = i_head block->height + 1;
	//	sprintf(temp, "%d", new_block->height);
	//	strcat(concateData, temp);
	new_block->time_stamp = get_current_time_stamp();
	//	sprintf(temp, "%d", new_block->time_stamp);
	//	strcat(concateData, temp);
	new_block->prev_hash = i_head block->hash;
	//	sprintf(temp, "%d", new_block->prev_hash);
	//	strcat(concateData, temp);
	new_block->nonce = generate_random_positive_integer();
	//	sprintf(temp, "%d", new_block->nonce);
	//	strcat(concateData, temp);
	new_block->relayed_by = //TODO: take from the appropriate field in the client()
	//	sprintf(temp, "%d", new_block->prev_hash);
	//	strcat(concateData, temp);
		new_block->hash = //createHash(cocateData);
	/*
	int diff = checkDifficulty(new_block->hash);
		if(diff >= 16){
		new_block->difficulty = diff;
		 isValidBlock = true;
		 }
		}
	*/
		return new_block;

}

//Gabi said we should use library function and not out imple'
Uint crc32b(unsigned char *message)
{
	int i, j;
	unsigned int byte, crc, mask;

	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0) {
		byte = message[i];            // Get next byte.
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--) {    // Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return ~crc;
}

/*
###########Netanel 26.12
########### Updated 27.12
###########Functions:
1. createGenesis   - making the first node
 - No need check the difficulty of the hash
 - Need define constant value for initial genesis,
 such as: const GENESIS_VAL
 Implenention:
 bitcoin_block_data* createGenesis() {

		bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
		new_block->height = GENESIS_VAL;
		new_block->time_stamp = get_current_time_stamp();
		new_block->prev_hash = GENESIS_VAL;
		new_block->difficulty = GENESIS_VAL;
		new_block->nonce = GENESIS_VAL;
		new_block->relayed_by = GENESIS_VAL;
		new_block->hash = createHash(get_current_time_stamp());
		return new_block;
}
########################################
2. concateAll	   - taking all data from a node and concate all
I made this in the initializing function
3. createHash	   - creating the conacted from above and make it's hash
Implenetion:
Uint createHash(unsigned char* data) {
	return(crc32(0L, data, 5));
}
- Only call to crc32 function with the data
4. checkDifficulty - checking the difficulyt of 3
Implementions:
int checkDifficulty(Uint hash, int difficulty) {
	return (1 ≪(sizeof(i_hash) * 8 - i_difficulty) - 1);
}


*/
