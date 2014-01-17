#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"
#include "util.h"

	

/* globals */
extern int error_code; 

/* datatypes */
struct Graph {
	int verticies;
	int** matrix;
};

/* private methods */
int _clamp(int i){
	if(i > MAX_DIST){
		return INF_DIST;
	} else {
		return i;
	}
}


/* we declare getters and setters so that tsgraph can deal with an opaque */
/* struct */
int _get_element(Graph* self, int row, int column){
	return self->matrix[row][column];
}

void _set_element(Graph* self, int row, int column, int val){
	assert((MAX_DIST >= val) || (val == INF_DIST));
	self->matrix[row][column] = val;
}


void _update_dist(Graph* self, int i, int j, int k){
	int old_val = _clamp(self->matrix[i][j]);
	int new_val = _clamp(self->matrix[i][k] + self->matrix[k][j]);

	_set_element(self, i, j,  old_val > new_val ? new_val : old_val);
}
void _update_dists(Graph* self, int k){
	for(int i = 0; i < self->verticies; i++){
		for(int j = 0; j < self->verticies; j++){
			_update_dist(self, i, j, k);
		}
	}
}

/* public methods */
Graph* solve_graph(Graph* self){
	for(int k = 0; k < self->verticies; k++){
		_update_dists(self, k);
	}
	return self; 				/* for convenience */
}

void print_graph(Graph* self){
	printf("Printing a %i-vertex graph\n", self->verticies);

	for(int i = 0; i < self->verticies; i++){
		for(int j = 0; j < self->verticies; j++){
			printf("%i ", self->matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
			

bool graph_eq(Graph* g1, Graph* g2){
	if(!(g1 && g2) || g1->verticies != g2->verticies){
		return false;
	}
	for(int i = 0; i < g1->verticies; i++){
		for(int j = 0; j < g1->verticies; j++){
			if(g1->matrix[i][j] != g2->matrix[i][j]){
				return false;
			}
		}
	}

	return true;
}

int get_verticies(Graph* self){
	LOGGER();
	printf("%i\n", self->verticies);
	return self->verticies;
}

/* Constructors: */
Graph* graph_from_file(FILE *f){
	assert(f);
	Graph* ret;
	int** matrix;
	int next_el;

	ret = malloc(sizeof(Graph));

	/* TODO: error handling */
	HANDLE(fscanf(f, "%i", &ret->verticies));

	if(ret->verticies){
		HANDLE(matrix = malloc(ret->verticies * sizeof(int*)));
		for(int i = 0; i < ret->verticies; i++){
			HANDLE(!(matrix[i] = malloc(ret->verticies * sizeof(int))));
		}
	} else {
		matrix = NULL;
	}

	for(int i = 0; i < ret->verticies; i++){
		for(int j = 0; j < ret->verticies; j++){
			if(fscanf(f, "%i",  &next_el)){
				matrix[i][j] = next_el;
			} else {
				printf("Bad file.\n");
				exit(MALFORMED_INPUT_ERROR);
			}
		}
	}

	ret->matrix = matrix;
	fclose(f);
	return ret;
}

/* Destructors: */
void free_graph(Graph* self){
	for(int i = 0; i < self->verticies; i++){
		free(self->matrix[i]);
	}
	free(self->matrix);
	free(self);
 }
