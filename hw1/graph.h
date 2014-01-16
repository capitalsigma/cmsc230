#pragma once

#include <stdbool.h>

/* error codes */
#define INVALID_INPUT_ERROR 1
#define MALFORMED_INPUT_ERROR 2

/* constants */
#define INF_DIST 10000000
#define MAX_DIST 1000

/* globals */
int error_code;

/* datatypes */
/* struct Graph; */
typedef struct Graph Graph;


/* Methods */
int _get_element(Graph* self, int row, int column);
void _set_element(Graph* self, int row, int column, int val);
void _update_dist(Graph* self, int i, int j, int k);
void _update_dists(Graph* self, int k);
bool graph_eq(Graph* g1, Graph* g2);
int get_verticies(Graph* self);
Graph* solve_graph(Graph* self);
void print_graph(Graph* self);

/* Constructors: */
Graph* graph_from_file(FILE *f);

/* Destructors: */
void free_graph(Graph* g);
