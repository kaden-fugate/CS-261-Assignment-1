 /** EXTRA CREDITS **/

 /*
 * This file is where you should implement your doubly-linked list.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function). Feel free to implement any additional
 * functions you might need. Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Kaden "The Kadenator" Fugate
 * Email: fugatka@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "db_list.h"

/*
 * This structure is used to represent a single node in a doubly-linked list.
 * It is not defined in db_list.h, so it is not visible to the user. You should not
 * modify this structure.
 */
struct db_node
{
    void* val;
    struct db_node* prev; // a pointer to the previous node
    struct db_node* next; // a pointer to the next node
};

/*
 * This structure is used to represent an entire doubly-linked list. Note that
 * we're keeping track of both the head and the tail of the list here.
 */
struct db_list
{
    struct db_node* head;
    struct db_node* tail;
};

/*
 * This function should allocate and initialize a new, empty doubly linked list and
 * return a pointer to it.
 *
 * Note: it is your choice to include sentinels or not
 */
struct db_list* db_list_create()
{
    struct db_list *temp = malloc( sizeof( struct db_list ) );
    temp->head = NULL, temp->tail = NULL;

    return temp;
}

/*
 * This function should free the memory associated with a doubly-linked list. In
 * particular, while this function should up all memory used in the list
 * itself (i.e. the space allocated for all of the individual nodes), it should
 * not free any memory allocated to the pointer values stored in the list. In
 * other words, this function does not need to free the `val` fields of the
 * list's nodes.
 *
 * Params:
 * db_list - the doubly-linked list to be destroyed. May not be NULL.
 */

void db_list_free(struct db_list* db_list)
{

    struct db_node *temp = db_list->head;

    while(temp){ // iterate and free until list empty

        db_list->head = db_list->head->next;
        free(temp);
        temp = db_list->head;

    }

    free(db_list);
}

/*
 * This function should insert a new value into a given doubly-linked list.
 * Importantly, this function will need to allocate a new `struct db_node` in
 * which to store the new value and add that node at the head of the list. 
 * This function should only insert elements at the *beginning* of
 * the list. In other words, it should always insert the new element as the
 * head of the list.
 *
 * Params:
 * db_list - the doubly-linked list into which to insert an element. May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void db_list_insert(struct db_list* db_list, void* val)
{
    struct db_node *new = malloc( sizeof( struct db_node ) ); // initialize new db_node
    new->val = val, new->prev = NULL, new->next = db_list->head; // new head always has NULL prev pointer

    if(db_list->head){ db_list->head->prev = new; } // old head's prev pointer points to new head

    db_list->head = new; 
    if( !db_list->tail ){ db_list->tail = new; } // if tail doesnt exist yet, tail is now head
}

/*
 * This function should insert a new value into a given doubly-linked list.
 * Importantly, this function will need to allocate a new `struct db_node` in
 * which to store the new value and add that node at the tail of the list.  
 * This function should only insert elements at the *end* of
 * the list. In other words, it should always insert the new element as the
 * tail of the list.
 *
 * Params:
 * db_list - the doubly-linked list into which to insert an element.  May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void db_list_insert_end(struct db_list* db_list, void* val)
{
    struct db_node *new = malloc( sizeof( struct db_node ) ); // initialize new node
    new->val = val, new->prev = db_list->tail, new->next = NULL; // prev will point to tail, next will be null

    if(db_list->tail){ db_list->tail->next = new; } // if the tail exists, its next node will point to the new tail
    db_list->tail = new; // tail in db_list points to new node

    if( !db_list->head ){ db_list->head = new; } // if list was empty, head points to tail which is both head and tail now

}


/*
 * This function should remove the last element from a given doubly-linked list. 
 * If the list is empty, this function doesn't need to do anything.
 * Importantly, this function will also need to free the
 * memory held by the node being removed (it does not need to free the stored
 * value itself, just the node).

 * Params:
 * db_list - the doubly-linked list from which to remove an element. May not be NULL.

 */
void db_list_remove_end(struct db_list* db_list)
{
    if( !db_list->tail ){ return; } // if list empty, do nothing

	struct db_node *temp = db_list->tail;

    db_list->tail = db_list->tail->prev; // tail points to prev node
    db_list->tail->next = NULL; 

    free(temp);

}


/*
 * This function should display/print all the elements of the given doubly-linked list 
 * from beginning to the end. 
 *
 * This function will be passed a *function pointer* called `p` that you
 * should use to print the value of `val` of each db_node.
 * 
 * For example, part of your code here might look something like this (assuming
 * you're printing the 'val' of a specific db_list node):
 * 
 * p(db_node->val)
 *
 * Params:
 * db_list - the doubly-linked list from which to display. May not be NULL.
 * cmp - pointer to a function that can be passed one void* value from
 *     to print it out, as described above.
 */
void db_list_display_forward(struct db_list* db_list, void (*p)(void* a))
{

	struct db_node *temp = db_list->head;

    while(temp){ // iterate until null and print val

        (*p)(temp->val);
        temp = temp->next;

    }

}

/*
 * This function should display/print all the elements of the given doubly-linked list 
 * from the end to the beginning. 
 *
 * This function will be passed a *function pointer* called `p` that you
 * should use to print the value of `val` of each db_node.
 * 
 * For example, part of your code here might look something like this (assuming
 * you're printing the 'val' of a specific db_list node):
 * 
 * p(db_node->val)
 *
 * Params:
 * db_list - the doubly-linked list from which to display. May not be NULL.
 * cmp - pointer to a function that can be passed one void* value from
 *     to print it out, as described above.
 */
void db_list_display_backward(struct db_list* db_list, void (*p)(void* a))
{

	struct db_node *temp = db_list->tail;

    while(temp){ // iterate until NULL and print val

        (*p)(temp->val);
        temp = temp->prev;

    }

}

