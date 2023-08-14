#pragma once
#include "NonDirectedGraph.h"
#include "DirectedGraph.h"
#include "Exceptions.h"

//Responsible for handling IO from the user and the program.
class io_manager
{
private:

public:
	static void run_program();
	static graph* get_user_input();
	static void get_graph_input(graph* i_graph, int& o_completed_edges);
	static void get_edge_input(int& o_src, int& o_dst, int i_num_of_vertexes);
	static void get_vertexes_and_edges_input(int& o_vertexes, int& o_edges);
};