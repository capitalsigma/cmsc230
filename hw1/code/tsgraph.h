#pragma once

#include "graph.h"
#include "util.h"

/* Object type */
typedef struct TSGraph TSGraph;

/* Methods: */
Graph* get_graph(TSGraph* self);
TSGraph* _update_dist_p(TSGraph* self, int i_start, int i_end);
TSGraph* solve_tsgraph(TSGraph* self);

/* Constructor: */
TSGraph* tsgraph_from_graph(Graph* graph, int num_threads);

/* Destructor: */
void free_tsgraph(TSGraph* self);
void deep_free_tsgraph(TSGraph* self);
