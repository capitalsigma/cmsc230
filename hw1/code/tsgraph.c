#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include "graph.h"
#include "util.h"
#include "tsgraph.h"


/* _DistArgs definitions */
typedef struct {
	TSGraph* tsgraph;
	int i_start;
	int i_end;
}  _DistArgs;


/* Constructor: */
_DistArgs* _make_dist_args(TSGraph* tsgraph, int i_start, int i_end){
	_DistArgs* ret = malloc(sizeof(_DistArgs));
	
	ret->tsgraph = tsgraph;
	ret->i_start = i_start;
	ret->i_end = i_end;

	return ret;
}

/* Destructor: */
/* NB: does not free the TSGraph it contains */
void _free_dist_args(_DistArgs* args){
	free(args);
}


/* TSGraph definitions */
struct TSGraph {
	Graph* graph;
	int num_threads;
	pthread_barrier_t *barrier;
};

/* Methods: */
Graph* get_graph(TSGraph* self){
	return self->graph;
}


void _update_dists_p(TSGraph* self, int i_start, int i_end){
	int max_k = get_verticies(get_graph(self));
	for(int k = 0; k < max_k; k++){
		for(int i = i_start; i < i_end; i++){
			for(int j = 0; j < max_k; j++){
				_update_dist(get_graph(self), i, j, k);
			}
		}
		pthread_barrier_wait(self->barrier);
	}
}

void* _update_dist_p_wrapper(void* arguments){
	_DistArgs* args = (_DistArgs*)arguments;
	_update_dists_p(args->tsgraph, args->i_start, args->i_end);
	_free_dist_args(args);
	pthread_exit(NULL);
}



/* TSGraph* _update_dists_p(TSGraph* self); */
TSGraph* solve_tsgraph(TSGraph* self){
	int vert = get_verticies(get_graph(self));
	int chunk = vert / self->num_threads;
	pthread_t threads[self->num_threads];

	for(int i = 0; i < self->num_threads; i++){
		_DistArgs* args = _make_dist_args(self, i * chunk,  (i + 1) * chunk);
		HANDLE(pthread_create(&threads[i], NULL, _update_dist_p_wrapper, 
		                       args));
		/* _free_dist_args(args); */
	}
	
	for(int i = 0; i < self->num_threads; i++){
		HANDLE(pthread_join(threads[i], NULL));
	}

	return self;
}	

/* Constructor: */
TSGraph* tsgraph_from_graph(Graph* graph, int num_threads){
	assert(num_threads);
	int vert = get_verticies(graph);
	TSGraph* ret = malloc(sizeof(TSGraph));

	if(!(ret->num_threads = num_threads > vert ? vert : num_threads)){
		ret->num_threads = 1;
	}

	ret->graph = graph;
	HANDLE(!(ret->barrier = malloc(sizeof(pthread_barrier_t))));
	HANDLE(pthread_barrier_init(ret->barrier, NULL, ret->num_threads));

	return ret;
}

/* Destructor: */
void free_tsgraph(TSGraph* self){
	HANDLE(pthread_barrier_destroy(self->barrier));
	free(self->barrier);
	free(self);
}

void deep_free_tsgraph(TSGraph* self){
	Graph* graph = self->graph;
	free_tsgraph(self);
	free_graph(graph);
}

