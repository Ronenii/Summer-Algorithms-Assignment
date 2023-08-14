#pragma once


// Forward declaration
#include "DirectedGraph.h"

class non_directed_graph: public graph
{
public:
	non_directed_graph(int i_num_of_vertexes, int i_num_of_edges) :graph(i_num_of_vertexes, i_num_of_edges) {}
	~non_directed_graph() = default;
	void set_edge(vertex& i_src, vertex& i_dst) override;
    void set_edge(int i_src, int i_dst) override;
	void mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex) override;
	void visit_and_direct(vertex& i_vertex, graph& i_directed_graph);
	bool is_even_degrees();
    void stronglyConnectedComponents();
    vector<vertex>  transpose(vector<vertex> &i_vertexes);
	vector<pair<int, int>> find_bridges() override;
	graph* get_dummy_graph() override;
    bool is_connected() override;
	directed_graph* get_directed_graph();

};