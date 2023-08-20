#pragma once


// Forward declaration
#include "DirectedGraph.h"

class non_directed_graph: public graph
{
private:
	void mark_strongly_connected_components(directed_graph* transposed_graph, list<vertex>& ending_list);
	void set_ending_list_white(list<vertex>& ending_list);

public:
	non_directed_graph(const int i_num_of_vertexes, const int i_num_of_edges) :graph(i_num_of_vertexes, i_num_of_edges) {}
	~non_directed_graph() = default;
	void set_edge(vertex& i_src, vertex& i_dst) override;
    void set_edge(const int i_src, const int i_dst) override;
	void mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex) override;
	void visit_and_direct(vertex& i_vertex, graph& i_directed_graph, list<vertex>& ending_list, const int parent);
    vector<vector<int>> stronglyConnectedComponents();
    vector<vertex> transpose(vector<vertex> &i_vertexes);
	vector<pair<int, int>> find_bridges(vector<pair<int, int>> i_edges) override;
	vector<pair<int, int>>& scan_for_bridges(directed_graph& directed_graph_transposed,
	                                         const vector<pair<int, int>>& i_edges);
	graph* get_dummy_graph() override;
    bool is_connected() override;
	bool edge_exists(const int i_src, const int i_dst) override;
	directed_graph* get_directed_graph(list<vertex>& ending_list);
	vertex& get_real_neighbor(vertex& i_src) override { return m_vertexes[i_src.get_value() - 1]; }

};