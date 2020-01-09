#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include "../include/linked_list.h"
#include "../include/bitcoin.h"
#include "../include/utility.h"
#include "../include/miner.h"
#include "../include/dummy_miner.h"

bitcoin_block_data* currCandidate;

void
print_block_acceptance();

void
print_block_rejection();

void
initialize_list_with_genesis(Singly_Linked_List* blockchain);

void
destroy_srv(pthread_t threads_ids[]);

pthread_t*
initialize_srv();

PUBLIC
void 
server()
{
	Singly_Linked_List blockchain;
	initialize_list_with_genesis(&blockchain);
    pthread_t* threadsIds = initialize_srv();
	//bitcoin_block_data* checked_block = g_proposed_srv_head;
	pthread_cond_broadcast(&wait_start_mine);
    logBit("Start running server");
	while(blockchain.length < 100){
	    pthread_mutex_lock(&set_block_lock);
	    pthread_cond_wait(&new_block_arrive, &set_block_lock);
        currCandidate = g_proposed_srv_head;  // need to copy block
        pthread_mutex_unlock(&set_block_lock);
        logBit("verify block");
	    if (verify_block(currCandidate))
        {
            logBit("adding block");
            append_To_List(&blockchain, currCandidate);
            print_block_acceptance();
        }
        else
        {
            logBit("reject block");
            print_block_rejection();
            free(currCandidate);
        }
	}

    destroy_List(&blockchain);
	destroy_srv(threadsIds);
}

PRIVATE
void
initialize_list_with_genesis(Singly_Linked_List* blockchain)
{
	blockchain = initialize_Empty_List(
						  sizeof(bitcoin_block_data),
						  release_bitcoin_block_data);

	bitcoin_block_data* genesis_block = createGenesis();
	
	append_To_List(blockchain, genesis_block);
	g_curr_srv_head = genesis_block;
	//free(genesis_block);
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
pthread_t*
initialize_srv(){
    setpriority(PRIO_PROCESS, 0, -20);
    programInit();
    int i;
    pthread_t* thread_ids = (pthread_t*)malloc(sizeof(pthread_t) * (NUM_OF_MINERS + 1));
    for(i = 0; i < NUM_OF_MINERS; ++i){
            pthread_create(&thread_ids[i], NULL, programLoop, NULL);
    }

    pthread_create(&thread_ids[NUM_OF_MINERS], NULL, programFalseLoop, NULL);
    return thread_ids;
}

PRIVATE
void
destroy_srv(pthread_t threads_ids[]){
    int i;
    for (i = 0; i < NUM_OF_MINERS; ++i){
        pthread_cancel(threads_ids[i]);
    }
    pthread_cancel(threads_ids[NUM_OF_MINERS]); // dummy thread
    fclose(logFile);
    programDestroy();

}

int main(){
    server();
}