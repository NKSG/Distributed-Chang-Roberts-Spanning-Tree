/*
 * LinkedList.h
 *
 *  Created on: Jan 25, 2012
 *      Author: dustevil
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdbool.h>
#include "DCRST.h"
/*****************************************************************************
 *                                                                            *
 *  Define a structure for linked list elements.                              *
 *                                                                            *
 *****************************************************************************/
typedef struct ListElmt_ {
	struct Mote_ *data;
	struct QueueElmt_ *next;
} ListElmt;
/*****************************************************************************
 *                                                                            *
 *  Define a structure for linked lists.                                      *
 *                                                                            *
 *****************************************************************************/
typedef struct List_ {
	unsigned int size;
	ListElmt *head;
	ListElmt *tail;
} List;
/*****************************************************************************
 *                                                                            *
 *  --------------------------- Public Interface ---------------------------  *
 *                                                                            *
 *****************************************************************************/
void list_init(List *list);
_Bool list_insert(List *list, const struct Mote_ *data);
int list_rem_elmt(List *list, struct Mote_ *element, struct Mote_ **data);
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif /* LINKEDLIST_H_ */
