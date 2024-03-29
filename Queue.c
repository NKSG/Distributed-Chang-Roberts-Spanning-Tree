/*
 * Queue.c
 *
 *  Created on: Dec 31, 2011
 *      Author: dustevil
 */

/*****************************************************************************
 *                                                                            *
 *  -------------------------------- queue.c --------------------------------  *
 *                                                                            *
 *****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
/*****************************************************************************
 *                                                                            *
 *  ------------------------------- queue_init ------------------------------  *
 *                                                                            *
 *****************************************************************************/
void queue_init(Queue *queue) {
	/*****************************************************************************
	 *                                                                            *
	 *  Initialize the queue.                                                      *
	 *                                                                            *
	 *****************************************************************************/
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	return;
}
/*****************************************************************************
 *                                                                            *
 *  ----------------------------- queue_ins_next ----------------------------  *
 *                                                                            *
 *****************************************************************************/
int queue_insert(Queue *queue, const Message *data) {
	QueueElmt *new_element;

	/*****************************************************************************
	 *                                                                            *
	 *  Allocate storage for the element.                                         *
	 *                                                                            *
	 *****************************************************************************/
	if ((new_element = (QueueElmt *) malloc(sizeof(QueueElmt))) == NULL)
		return -1;
	new_element->data = data;
	/*****************************************************************************
	 *                                                                            *
	 *  Insert the element into the tail of the queue.                                         *
	 *                                                                            *
	 *****************************************************************************/
	new_element->next = NULL;
	if (queue->size == 0) {
		queue->head = new_element;
		queue->tail = new_element;
	} else {
		queue->tail->next = new_element;
		queue->tail = new_element;
	}

	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the queue to account for the inserted element.          *
	 *                                                                            *
	 *****************************************************************************/
	queue->size++;
	return 0;
}
/*****************************************************************************
 *                                                                            *
 *  ----------------------------- queue_rem_next ----------------------------  *
 *                                                                            *
 *****************************************************************************/
int queue_remove_first(Queue *queue, Message **data) {
	/*****************************************************************************
	 *                                                                            *
	 *  Do not allow removal from an empty queue.                                  *
	 *                                                                            *
	 *****************************************************************************/
	if (queue_size(queue) == 0)
		return -1;
	/*****************************************************************************
	 *                                                                            *
	 *  Remove the head of the queue.                                         *
	 *                                                                            *
	 *****************************************************************************/

	*data = queue->head->data;
	queue->head = queue->head->next;
	if (queue_size(queue) == 1)
		queue->tail = NULL;
        
	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the queue to account for the removed element.           *
	 *                                                                            *
	 *****************************************************************************/
	queue->size--;
	return 0;
}
