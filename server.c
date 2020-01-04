#include <sys/time.h>
#include <sys/resource.h>
#include "../include/linked_list.h"
#include "../include/bitcoin.h"
#include "bitcoin.c"
#include "utility.h"
#include "miner.h"
#include "dummy_miner.h"

bitcoin_block_data* currCandidate;

void
print_block_acceptance();

void
print_block_rejection(Uint);

PUBLIC
void 
server()
{
	Singly_Linked_List blockchain;
	initialize_list_with_genesys(&blockchain);
    programInit();
	bitcoin_block_data checked_block = g_proposed_srv_head;
	pthread_cond_broadcast(&wait_start_mine);

	while(blockchain.length < 100){
	    pthread_mutex_lock(&set_block_lock);
	    pthread_cond_wait(&new_block_arrive, &set_block_lock);
        currCandidate = g_proposed_srv_head;
        pthread_mutex_unlock(&set_block_lock);

	    if (verify_block(currCandidate))
        {
            append_To_List(&blockchain, currCandidate);
            print_block_acceptance();
        }
        else
        {
            print_block_rejection();
            free(currCandidate);
        }

	}

    destroy_List(&blockchain);
	destroy_srv();
}

PRIVATE
void
initialize_list_with_genesys(Singly_Linked_List* blockchain)
{
	initialize_Empty_List(blockchain,
						  sizeof(bitcoin_block_data),
						  release_bitcoin_block_data);

	bitcoin_block_data genesys_block = createGenesis();
	
	append_To_List(&blockchain, genesis_block);
	g_curr_srv_head = genesys_block;
	free(genesys_block);
}

PRIVATE
void
print_block_acceptance()
{
	printf("Server: New block added by %d, attributes: ", 
			currCandidate->relayed_by);
	print_bitcoin_block_data(currCandidate);
	printf("\n");
}

PRIVATE
void
print_block_rejection()
{
	printf("Wrong hash for block #%d by miner %d, received %d but calculated %d",
		    currCandidate->height,
            currCandidate->relayed_by,
            currCandidate->hash,
            calculatedHash);
}

PRIVATE
int*
initialize_srv(){
    setpriority(PRIO_PROCESS, 0, -20);
    programInit();
    int i;
    pthread_t thread_ids[NUM_OF_MINERS + 1];
    for(i = 0; i < NUM_OF_MINERS; ++i){
            pthread_create(&thread_ids[i], NULL, programLoop, NULL);
    }

    pthread_create(&thread_ids[NUM_OF_MINERS], NULL, programFalseLoop, NULL);
}

PRIVATE
void
destroy_srv(pthread_t threads_ids[]){
    int i;
    for (i = 0; i < NUM_OF_MINERS; ++i){
        pthread_cancel(threads_ids[i]);
    }
    pthread_cancel(threads_ids[NUM_OF_MINERS]); // dummy thread
    programDestroy();

}

int main(){
    server();
}