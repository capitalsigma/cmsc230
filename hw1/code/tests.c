#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "util.h"
#include "graph.h"
#include "tsgraph.h"
#include "tests.h"

/* TODO: add cases to check the exceptions being raised */

#define EMPTY_GRAPH "input/empty.txt" /* written */
#define HORIZONTAL_GRAPH "input/horizontal.txt" /* written */
#define CIRCULAR_GRAPH "input/circular.txt" /* written */
#define MAX_DIST_GRAPH "input/max_dist.txt" /* written */

#define EMPTY_GRAPH_ANS "input/empty.txt"
#define HORIZONTAL_GRAPH_ANS "input/horizontal_ans.txt"
#define CIRCULAR_GRAPH_ANS "input/circular_ans.txt"
#define MAX_DIST_GRAPH_ANS "input/max_dist_ans.txt"


/* #define TEST(gr) _check_ ## gr ( solve_graph( gr )) */

#define PG(gr) printf("printing %s\n", #gr); print_graph(gr)
#define PS(msg) printf("%s\n", msg)

bool _check_ans(Graph* g1, char* path){
	FILE* f = fopen(path, "r");
	Graph* g2 = graph_from_file(f);
	bool ret = graph_eq(g1, g2);

	free_graph(g2);

	return ret;	
	/* fclose(f); */
}

void _check_empty(Graph* g1){
	LOGGER();
	ASSERT(_check_ans(g1, EMPTY_GRAPH_ANS));
}

void _check_horiz(Graph* g1){
	LOGGER();
	PG(g1);
	ASSERT(_check_ans(g1, HORIZONTAL_GRAPH_ANS));
}

/* void _check_vert(Graph* g1){ */
/* 	ASSERT(_check_ans(g1, VERTICAL_GRAPH_ANS)); */
/* } */

void _check_circ(Graph* g1){
	LOGGER();
	ASSERT(_check_ans(g1, CIRCULAR_GRAPH_ANS));
}

void _check_max_dist(Graph* g1){
	LOGGER();
	ASSERT(_check_ans(g1, MAX_DIST_GRAPH_ANS));
}

void test_graph(){
	Graph *empty, *horiz, *circ, *max_dist;
	/* FILE *empty_f, *horiz_f, *vert_f; */
	empty = graph_from_file(fopen(EMPTY_GRAPH, "r"));
	PS("empty");
	horiz = graph_from_file(fopen(HORIZONTAL_GRAPH, "r"));
	PS("horiz");
	/* vert = graph_from_file(fopen(VERTICAL_GRAPH, "r")); */
	circ = graph_from_file(fopen(CIRCULAR_GRAPH, "r"));
	PS("circ");
	max_dist = graph_from_file(fopen(MAX_DIST_GRAPH, "r"));
	PS("max");

	ASSERT(get_verticies(empty) == 0);
	ASSERT(get_verticies(horiz) == get_verticies(circ));
	ASSERT(get_verticies(max_dist) == 3);

	SMALL_SEP();

	ASSERT(graph_eq(empty, empty));
	ASSERT(graph_eq(horiz, horiz));
	ASSERT(graph_eq(circ, circ));
	/* ASSERT(graph_ep(vert, vert)); */

	SMALL_SEP();

	PG(horiz);
	PG(empty);
	PG(circ);

	SMALL_SEP();

	ASSERT(!graph_eq(empty, horiz));
	ASSERT(!graph_eq(horiz, circ));
	ASSERT(!graph_eq(NULL, horiz));
	ASSERT(!graph_eq(NULL, empty));

	SMALL_SEP();

	_check_empty(solve_graph(empty));
	_check_horiz(solve_graph(horiz));
	/* TEST(solve_graph(vert)); */
	_check_circ(solve_graph(circ));
	_check_max_dist(solve_graph(max_dist));

	SMALL_SEP();

	free_graph(empty);
	free_graph(horiz);
	free_graph(circ);
	free_graph(max_dist);
}


void test_tsgraph(){
	Graph *empty, *horiz, *circ, *max_dist;
	TSGraph *ts_empty, *ts_horiz, *ts_circ, *ts_max_dist;
	
	empty = graph_from_file(fopen(EMPTY_GRAPH, "r"));
	horiz = graph_from_file(fopen(HORIZONTAL_GRAPH, "r"));
	circ = graph_from_file(fopen(CIRCULAR_GRAPH, "r"));
	max_dist = graph_from_file(fopen(MAX_DIST_GRAPH, "r"));

	for(int i = 1; i < 10; i++){
		ts_empty = tsgraph_from_graph(empty, i);
		ts_horiz = tsgraph_from_graph(horiz, i);
		ts_circ = tsgraph_from_graph(circ, i);
		ts_max_dist = tsgraph_from_graph(max_dist, i);

		_check_empty(get_graph(solve_tsgraph(ts_empty)));
		_check_horiz(get_graph(solve_tsgraph(ts_horiz)));
		_check_circ(get_graph(solve_tsgraph(ts_circ)));
		_check_max_dist(get_graph(solve_tsgraph(ts_max_dist)));

		free_tsgraph(ts_empty);
		free_tsgraph(ts_horiz);
		free_tsgraph(ts_circ);
		free_tsgraph(ts_max_dist);
	}

	free_graph(empty);
	free_graph(horiz);
	free_graph(circ);
	free_graph(max_dist);


}


int main(int argc, char* argv[]){
	BIG_SEP();

	test_graph();

	BIG_SEP();

	test_tsgraph();

	DONE();
}
