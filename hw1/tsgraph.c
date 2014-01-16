#include <pthread.h>

#include "graph.h"
#include "util.h"
#include "tsgraph.h"


/* _DistArgs definitions */
struct  _DistArgs {
	TSGraph* tsgraph;
	int i_start;
	int i_end;
};

/* Constructor: */
_DistArgs* _make_dist_args(TSGraph* tsgraph, int i_start, int i_end){
	_DistArgs* ret = malloc(sizeof(_DistArgs));
	
	ret->tsgraph = tsgraph;
	ret->i_start = i_start;
	ret->i_end = i_end;

	return ret;
}

/* TSGraph definitions */
struct TSGraph {
	Graph* graph;
	int num_threads;
}

/* Destructor: */
/* NB: does not free the TSGraph it contains */
void _free_dist_args(_DistArgs* args){
	free(args);
}

/* Methods: */
Graph* get_graph(TSGraph* self){
	return self->graph;
}

void _update_dists_p(TSGraph* self, int i_start, int i_end){
	int max_k = get_verticies(get_graph(self));
	for(int k = 0; k < max_k; k++){
		/* and now we do the actual algorithm */
		/* with a barrier at the end of each iteration of k */
	}
}

void* _update_dist_p_wrapper(_DistArgs* args){
	_update_dists_p(args->tsgraph, args->i_start, args->i_end);
	return NULL;
}



/* TSGraph* _update_dists_p(TSGraph* self); */
TSGraph* solve_tsgraph(TSGraph* self){
	/* TODO: we spawn all of the threads here */
	

/* bool still_working(TSGraph* self); */
/* int get_k(TSGraph* self); */

/* Constructor: */
TSGraph* tsgraph_from_graph(Graph* graph, int num_threads){
	TSGraph* ret = malloc(sizeof(TSGraph));

	ret->graph = graph;
	ret->num_threads = num->threads;

	return ret;
}

/* Destructor: */
void free_tsgraph(TSGraph* self){
	free(self);
}

void deep_free_tsgraph(TSGraph* self){
	free_graph(self->graph);
	free(self);
}

