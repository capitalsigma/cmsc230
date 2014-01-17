#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utilities/stopwatch.h"
#include "util.h"
#include "graph.h"
#include "tsgraph.h"

/* main.out path_to_file [nthreads] */
int main(int argc, char* argv[]){
	int nthreads = 0;
	Graph* graph;
	TSGraph* tsgraph;
	StopWatch_t stopwatch;

	if(argc == 0){
		printf("No file specified.\n");
		exit(1);
	} else if(argc == 2){
		nthreads = atoi(argv[2]);
	}

	graph = graph_from_file(fopen(argv[1], "r"));

	if(nthreads){
		tsgraph = tsgraph_from_graph(graph, nthreads);
		startTimer(&stopwatch);
		solve_tsgraph(tsgraph);
	
	

}



	
	
