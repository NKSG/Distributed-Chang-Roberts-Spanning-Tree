/*
 * Network-Topology.c
 *
 *  Created on: Dec 23, 2011
 *      Author: dustevil
 */
#include <stdlib.h>
#include "DCRST.h"
#include "Queue.h"

static void installCoverageAreas();

static Graph theTopology;
static Mote nullMote;

void initializeNetwork(const char *filename) {
	int index, y;

	open_file(filename);
	read_graph(&theTopology);

	for (index = 0; index < MAX_MOTE_COUNT; index++) {
                theTopology.adjList[index][0].ID = index;	
                theTopology.adjList[index][0].message_queue = (Queue *) malloc(sizeof(Queue));
		list_init(theTopology.adjList[index][0].message_queue);
		theTopology.adjList[index][0].state = OFF;
		for (y = 0; y < MAX_COVERED_MOTE_COUNT; y++) {
			theTopology.adjList[index][0].coverageArea[y] = &nullMote;
		}
		theTopology.adjList[index][0].coveredMoteCount = 0;
	}

	installCoverageAreas();
}

void installCoverageAreas() {
	int x, y;

	for (x = 0; x < theTopology.vcount; x++) {
		for (y = 0; y < theTopology.vcount; y++) {
			if (theTopology.adjList[x][y].weight > 0)
				theTopology.adjList[x][0].coverageArea[theTopology.adjList[x][0].coveredMoteCount++] = &theTopology.adjList[y][0];
		}
	}
}

Mote *getMote(const int index) {
	return &theTopology.adjList[index][0];
}

int getVCount() {
	return theTopology.vcount;
}

void printTopology() {
	int x, y;
	printf("%d\n", theTopology.vcount);
	for (x = 0; x < theTopology.vcount; x++) {
		for (y = 0; y < theTopology.vcount; y++)
			printf("%d ", theTopology.adjList[x][y].weight);
		putchar('\n');
	}
}
