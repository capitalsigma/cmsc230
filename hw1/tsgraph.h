#pragma once

#include "graph.h"
#include "util.h"

/* Object type */
typedef struct TSGraph TSGraph;

/* Methods: */
Graph* get_graph(TSGraph* self);
TSGraph* _update_dist_p(TSGraph* self, int i_start, int i_end);
void* _update_dist_p_wrapper(_DistArgs* args);
/* TSGraph* _update_dists_p(TSGraph* self); */
TSGraph* solve_tsgraph(TSGraph* self);
/* bool still_working(TSGraph* self); */
/* int get_k(TSGraph* self); */

/* Constructor: */
TSGraph* tsgraph_from_graph(Graph* graph, int num_threads);

/* Destructor: */
void free_tsgraph(TSGraph* self);
void deep_free_tsgraph(TSGraph* self);
