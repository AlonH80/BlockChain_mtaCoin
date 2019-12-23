/* ======================================================== */
/*   bitcoin.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "file_handler.h"
#include "bitcoin.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
bitcoin_block_data*
initialize_bitcoin_block_data();

EExecutionStatus 
validate_and_parse(char *line_to_parse, 
				   bitcoin_block_data *bitcoin_to_add);

int 
resolve_string(char *key);

void
assign_value(char **dest, char *src, size_t length);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE
bitcoin_block_data* 
initialize_bitcoin_block_data()
{
	bitcoin_block_data *new_btcn = malloc(sizeof(bitcoin_block_data));
	
	new_btcn->hash_value = NULL;
	new_btcn->height = NULL;
	new_btcn->total = NULL;
	new_btcn->time = NULL;
	new_btcn->received_time = NULL;
	new_btcn->relayed_by = NULL;
	new_btcn->prev_block = NULL;
	new_btcn->amount_of_parsed_fields = 0;
	new_btcn->total_amount_of_fields = TOTAL_AMOUNT_OF_FIELDS_TO_PARSE;

	return new_btcn;
}

PRIVATE
EExecutionStatus 
validate_and_parse(char *line_to_parse, bitcoin_block_data *bitcoin_to_add)
{
	char *value = NULL;
	
	if(!(value = strstr(line_to_parse, ":")))
	{
		fprintf(stderr, "Error while Proccessing string:\n%s", line_to_parse);
		return FAILURE;
	}
	
	int position = value - line_to_parse;
	char *field = calloc(position+1, sizeof(char));
	strncpy(field, line_to_parse, position);
	field[position] = '\0';	
	value++;
	
	switch (resolve_string(field)) 
	{
		case HASH: 			assign_value(&bitcoin_to_add->hash_value, 	 value, strlen(value));		break;
		
		case HEIGHT: 		assign_value(&bitcoin_to_add->height, 		 value, strlen(value));		break;
		
		case TOTAL: 		assign_value(&bitcoin_to_add->total, 		 value, strlen(value)); 	break;
		
		case TIME: 			assign_value(&bitcoin_to_add->time, 	     value, strlen(value));		break;
		
		case RECEIVED_TIME: assign_value(&bitcoin_to_add->received_time, value, strlen(value));		break;
		
		case RELAYED_BY: 	assign_value(&bitcoin_to_add->relayed_by,	 value, strlen(value)); 	break;
		
		case PREV_BLOCK: 	assign_value(&bitcoin_to_add->prev_block, 	 value, strlen(value));		break;
			 
		case BAD_FIELD_INPUT:	
			DEBUG
			return FAILURE;
	}		
	
	bitcoin_to_add->amount_of_parsed_fields++;
	
	if(bitcoin_to_add->amount_of_parsed_fields == bitcoin_to_add->total_amount_of_fields)
	{
		bitcoin_to_add->amount_of_parsed_fields = 0;
		return PARSED;
	}
	
	return SUCCESS;
}

PRIVATE
void
assign_value(char **dest, char *src, size_t length)
{
	char *pos = NULL;
	*dest = malloc((length+1)*sizeof(char));
		
	if ((pos = strchr(src, '\n')) != NULL)
		*pos = '\0';
	
	strcpy(*dest, src);
}

PRIVATE
int 
resolve_string(char *key)
{
    static field_type_struct lookuptable[] = 
	{
		{ "hash", HASH }, 
		{ "height", HEIGHT }, 
		{ "total", TOTAL }, 
		{ "time", TIME },
		{ "received_time", RECEIVED_TIME },
		{ "relayed_by", RELAYED_BY },
		{ "prev_block", PREV_BLOCK }
	};

	for (int i=0; i < TOTAL_AMOUNT_OF_FIELDS_TO_PARSE; i++) {
		  if (strcmp(lookuptable[i].key, key) == 0)
		  {
			return lookuptable[i].val;
		  }
    }
    return BAD_FIELD_INPUT;
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------
PUBLIC 
Singly_Linked_List* 
load_bitcoin_db(char* bc_db_f_name)
{
		//S_L_L is typedef for Singly_Linked_List
		S_L_L *bitcoin_db = initialize_Empty_List(sizeof(S_L_L),
												  release_bitcoin_block_data);												 			  

		bitcoin_block_data *bitcoin_to_add = initialize_bitcoin_block_data();
		char buffer[MAX_LEN];
		FILE *f_ptr;	
		char *line_buffer = malloc(sizeof(char)*MAX_LEN);
		EExecutionStatus parse_state = SUCCESS;
						  
		//in case of error while opening file, 
		//file_handler module will prompt the user and terminate.
		file_loader(bc_db_f_name, READ, &f_ptr);
				  
		//while (getline(&line_buffer, &length, f_ptr) != -1)
		while ((line_buffer = fgets(buffer, MAX_LEN, f_ptr)) != NULL)
		{	
			if(*line_buffer == '\n')
			{
				continue;
			}
			
			parse_state = validate_and_parse(line_buffer, bitcoin_to_add);
				  
			switch(parse_state)
			{
				case SUCCESS:					
					continue;
					break;
					
				case FAILURE:
					fprintf(stderr, "Error while Proccessing string:\n%s", line_buffer);
					free(line_buffer);
					release_bitcoin_block_data(bitcoin_to_add);
					return NULL;
						
				case PARSED:
					append_To_List(bitcoin_db, bitcoin_to_add);
					bitcoin_to_add = initialize_bitcoin_block_data();
					continue;
					
				default:
					fprintf(stderr, "WTF?! How did i get here?! :) \n");
			}
		}
		
		return bitcoin_db;
}

PUBLIC
void
print_bitcoin_block_data(bitcoin_block_data* block_to_print)
{
	printf("hash: ");
	printf("%s\n", block_to_print->hash_value);
	
	printf("height: ");
	printf("%s\n", block_to_print->height);	
	
	printf("total: ");
	printf("%s\n", block_to_print->total);	
	
	printf("time: ");
	printf("%s\n", block_to_print->time);	
	
	printf("received_time: ");
	printf("%s\n", block_to_print->received_time);	
	
	printf("relayed_by: ");
	printf("%s\n", block_to_print->relayed_by);	
	
	printf("prev_block: ");
	printf("%s\n", block_to_print->prev_block);	
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