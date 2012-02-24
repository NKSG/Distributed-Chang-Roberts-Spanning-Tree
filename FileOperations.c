/*
 * FileOp.c
 *
 *  Created on: Dec 8, 2011
 *      Author: dustevil
 */
#include <stdlib.h>
#include <stdio.h>
#include "DCRST.h"

#define NVER 100

static FILE *file_fp = NULL;

void open_file(const char *filename) {
	if ((file_fp = fopen(filename, "r")) == NULL)
		perror("Distributed Chang Robert Spanning Tree: can't open the file\n");
}

void read_graph(Graph *g) {
	char n_string[NVER];
	int n, weight;
	int x, y;
	char c;

	if (fscanf(file_fp, " %d", &n) < 0)
		perror("Distributed Chang Robert Spanning Tree: can't read the file\n");
	g->vcount = n;
	g->ecount = 0;
	for (x = 0; x < n; x++) {
		g->adjList[x][0].ID = x; // Naming each node with a identity number
		for (y = 0; y < n; y++) {
			if (fscanf(file_fp, " %d", &weight) < 0)
				perror("Distributed Chang Robert Spanning Tree: can't read the file\n");
			g->adjList[x][y].weight = weight; //Assigning weights to the edges
			if (weight > 0)
				g->ecount++; // Incrementing edge number by one accordingly
		}
	}
	fclose(file_fp);
}
