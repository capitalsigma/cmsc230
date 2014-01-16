#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"
#include "tsgraph.h"
#include "tests.h"

/* TODO: add cases to check the exceptions being raised */

#define EMPTY_GRAPH "input/empty.txt" /* written */
#define HORIZONTAL_GRAPH "input/horizontal.txt" /* written */
/* #define VERTICAL_GRAPH "input/vertical.txt"  */
#define CIRCULAR_GRAPH "input/cirular.txt" /* written */
#define MAX_DIST_GRAPH "input/max_dist.txt"

#define EMPTY_GRAPH_ANS "input/empty.txt"
#define HORIZONTAL_GRAPH_ANS "input/horizontal_ans.txt"
/* #define VERTICAL_GRAPH_ANS "input/vertical_ans.txt" */
#define CIRCULAR_GRAPH_ANS "input/cirular_ans.txt"
#define MAX_DIST_GRAPH_ANS "input/max_dist.txt"


#define TEST(gr) _check_ ## gr ## ( graph_solve( gr ))
#define PG(gr) printf("printing %s\n", #gr); print_graph(gr)
asdasdasd 

void _check_ans(Graph* g1, char* path){
	FILE* f = fopen(PATH);
	Graph* g2 = graph_from_file(f);

	ASSERT(graph_eq(g1, empty));

	/* fclose(f); */
}

void _check_empty(Graph* g1){
	_check_ans(g1, EMPTY_GRAPH_ANS);
}

void _check_horiz(Graph* g1){
	_check_ans(g1, HORIZONTAL_GRAPH_ANS);
}

/* void _check_vert(Graph* g1){ */
/* 	_check_ans(g1, VERTICAL_GRAPH_ANS); */
/* } */

void _check_circ(Graph* g1){
	_check_ans(g1, CIRCULAR_GRAPH_ANS);
}

void _check_max_dist(Graph* g1){
	_check_ans(g1, MAX_DIST_GRAPH_ANS);
}

void test_graph(){
	Graph *empty, *horizontal, *vertical;
	/* FILE *empty_f, *horiz_f, *vert_f; */
	empty = graph_from_file(fopen(EMPTY_GRAPH, "r"));
	horiz = graph_from_file(fopen(HORIZONTAL_GRAPH, "r"));
	/* vert = graph_from_file(fopen(VERTICAL_GRAPH, "r")); */
	circ = graph_from_file(fopen(CIRCULAR_GRAPH, "r"));
	max_dist  = graph_from_file(fopen(MAX_DIST_GRAPH, "r"));

	ASSERT(get_verticies(empty) == 0);
	ASSERT(get_verticies(horiz) == get_verticies(circ) == 5);
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

	TEST(empty);
	TEST(horiz);
	/* TEST(vert); */
	TEST(circ);
	TEST(max_dist);

	/* SMALL_SEP(); */
}


void test_tsgraph(){

}


int main(int argc, char* argv[]){
	BIG_SEP();

	test_graph();

	BIG_SEP();

	DONE();
}
