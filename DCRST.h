/*
 * DCRST.h
 *
 *  Created on: Dec 23, 2011
 *      Author: dustevil
 */

#ifndef DCRST_H_
#define DCRST_H_

#include <stdbool.h>
#include "Queue.h"
#include "LinkedList.h"

#define MAX_MOTE_COUNT 20
#define MAX_COVERED_MOTE_COUNT 10
#define MAX_MESSAGE_LENGHT 8
#define QUEUE_LENGHT 10

typedef enum {
	OFF = 0, IDLE, WAITING
} MoteState;

typedef enum {
	PROBE = 0, ECHO
} MessageType;

typedef struct Message_ {
	MessageType mtype;
	struct Mote_ *sender;
} Message;

typedef struct Mote_ {
	int ID;
	int weight;
	MoteState state;
	struct Queue_ *message_queue;
	struct Mote_ *coverageArea[MAX_COVERED_MOTE_COUNT];
	int coveredMoteCount;
} Mote;

typedef struct Graph_ {
	int vcount;
	int ecount;
	Mote adjList[MAX_MOTE_COUNT][MAX_MOTE_COUNT];
} Graph;

// The network topology's interface
void initializeNetwork();
void printTopology();
Mote *getMote(const int index);
int getVCount();

// File operations' interface
void open_file(const char *filename);
void read_graph(Graph *g);

#endif /* DCRST_H_ */
