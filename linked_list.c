/* ======================================================== */
/*   linked_list.c		      								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "linked_list.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
Singly_Linked_Node 
*allocate_list_cell(pVoid data_ptr);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------

PRIVATE 
Singly_Linked_Node* 
allocate_list_cell(pVoid data_ptr)
{
	//S_L_N is a Typedef for Singly_Linked_Node
    S_L_N *cell = malloc(sizeof(S_L_N));
    if(NULL == cell)
    {
        printf("Memory allocation error!\n");
        exit(1);
    }

    cell->data = data_ptr;
    cell->next = NULL;

    return cell;
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------
PUBLIC
Singly_Linked_List* 
initialize_Empty_List( size_t Element_Size, freeFunction free_Fn)
{
	Singly_Linked_List*  new_list = malloc(sizeof(Singly_Linked_List));
	new_list->head = new_list->tail = NULL;
	new_list->element_size = Element_Size;
	new_list->length = 0;
	new_list->freeFn = free_Fn;
	
	return new_list;
}
					  
PUBLIC
void 
append_To_List(Singly_Linked_List *list, pVoid element)
{
	Singly_Linked_Node *cell = allocate_list_cell(element);

	if(list->length == 0)
    {
        list->head = list->tail = cell;
    }
	else
    {
        list->tail->next = cell;
        list->tail = cell;
    }

  list->length++;
}

PUBLIC 
void
destroy_List(Singly_Linked_List *list)
{
	Singly_Linked_Node *current = list->head;

	while (current != NULL) {
		list->head = current->next;

		if (list->freeFn) {
			list->freeFn(current->data);
		}

		free(current->data);
		free(current);

		list->length--;

		current = list->head;
	}
}

PUBLIC
Singly_Linked_Node*
search_List(Singly_Linked_List *list, pVoid data)
{
		return NULL;//TODO - Write Search Function
}