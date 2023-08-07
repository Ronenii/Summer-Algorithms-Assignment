#pragma once

#include "DirectedGraph.h"

class non_directed_graph: public graph
{
public:
	non_directed_graph(int i_num_of_vertexes, int i_num_of_edges) :graph(i_num_of_vertexes, i_num_of_edges) {}
	~non_directed_graph() = default;
	virtual void set_edge(vertex& i_src, vertex& i_dst) override;
	virtual void mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex) override;
	directed_graph* create_directed_graph_with_dfs();
	void visit_and_direct(vertex& i_vertex, graph& i_directed_graph);
	bool is_even_degrees();
    vector<vertex> find_bridges();
	virtual graph* get_dummy_graph();
    virtual bool is_connected() override;
};