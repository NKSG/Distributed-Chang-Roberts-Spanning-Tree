/*
 * Queue.h
 *
 *  Created on: Dec 31, 2011
 *      Author: dustevil
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "DCRST.h"
/*****************************************************************************
 *                                                                            *
 *  Define a structure for linked queue elements.                              *
 *                                                                            *
 *****************************************************************************/
typedef struct QueueElmt_ {
	struct Mote_ *data;
	struct QueueElmt_ *next;
} QueueElmt;
/*****************************************************************************
 *                                                                            *
 *  Define a structure for linked queues.                                      *
 *                                                                            *
 *****************************************************************************/
typedef struct Queue_ {
	unsigned int size;
	QueueElmt *head;
	QueueElmt *tail;
} Queue;
/*****************************************************************************
 *                                                                            *
 *  --------------------------- Public Interface ---------------------------  *
 *                                                                            *
 *****************************************************************************/
void queue_init(Queue *queue);
int queue_insert(Queue *queue, const struct Message_ *data);
int queue_remove_first(Queue *queue, struct Message_ **data);
#define queue_size(queue) ((queue)->size)
#define queue_head(queue) ((queue)->head)
#define queue_tail(queue) ((queue)->tail)
#define queue_is_head(queue, element) ((element) == (queue)->head ? 1 : 0)
#define queue_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define queue_data(element) ((element)->data)
#define queue_next(element) ((element)->next)

#endif /* QUEUE_H_ */
