#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"
#include "util.h"

/* raises an error if expr is false */
/* #define TRY(expr, to_raise) MACRO_WRAP(if( expr ) { \
	

/* globals */
extern int error_code; 

/* datatypes */
struct {
	int verticies;
	int** matrix;
} Graph;

/* private methods */

/* we declare getters and setters so that tsgraph can deal with an opaque */
/* struct */
int _get_element(Graph* self, int row, int column){
	return self->matrix[row][column];
}

void _set_element(Graph* self, int row, int column, int val){
	self->matrix[row][column] = val;
}

void _update_dist(Graph* self, int i, int j, int k){
	int old_val = self->matrix[i][j];
	int new_val = self->matrix[i][k] + self->matrix[k][j];

	self->matrix[i][j] = old_val > new_val ? new_val : old_val;
}
void _update_dists(Graph* self, int k){
	for(int i = 0; i < self->verticies; i++){
		for(int j = 0; j < self->verticies; j++){
			_update_dist(self, i, j, k);
		}
	}
}

/* public methods */
void solve_graph(Graph* self){
	for(int k = 0; k < self->verticies; k++){
		_update_dists(self, k);
	}
}


void print_graph(Graph* self){
	printf("Printing a %i-vertex graph\n", self->vertex);

	for(int i = 0; i < self->verticies; i++){
		for(int j = 0; j < self->verticies; j++){
			printf("%i ", self->matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
			

bool graph_eq(Graph* g1, Graph* g2){
	if(g1->verticies != g2->verticies){
		return false;
	}
	for(int i = 0; i < g1->verticies; i++){
		for(int j = 0; j < g1->verticies; j++){
			if(g1->matrix[i][j] != g2->matrix[i][j]);
		}
	}

	return true;
}

int get_verticies(Graph* self){
	return self->verticies;
}

/* Constructors: */
Graph* graph_from_file(file *f){
	Graph* ret;
	int** matrix;
	int next_el;

	ret = malloc(sizeof(Graph));

	/* TODO: error handling */
	fscanf(f, "%i", &ret->verticies);

	if(ret->verticies){
		HANDLE(matrix = malloc(ret->verticies * sizeof(int*)));
		for(int i = 0; i < ret->verticies; i++){
			HANDLE(matrix[i] = malloc(ret->verticies * sizeof(int)));
		}
	} else {
		matrix = NULL;
	}

	for(int i = 0; i < ret->verticies; i++){
		for(int j = 0; j < ret->verticies; j++){
			if(fscanf(f, &next_el)){
				matrix[i][j] = next_el > MAX_DIST ? MAX_DIST : next_el;
			} else {
				printf("Bad file.\n");
				exit(MALFORMED_INPUT_ERROR);
			}
		}
	}

	ret->matrix = matrix;
	return ret;
}

/* Destructors: */
void free_graph(Graph* self){
	for(int i = 0; i < self->verticies; i++){
		free(self->matrix[i]);
	}
	free(self->matrix);
}
