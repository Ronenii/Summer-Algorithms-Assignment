#pragma once

#include "Graph.h"

class directed_graph: public graph
{
private:
    list<vertex> ending_list;
public:
    directed_graph(int i_num_of_vertexes, int i_num_of_edges) :graph(i_num_of_vertexes, i_num_of_edges) {}
    ~directed_graph() = default;
    void set_edge(vertex& i_src, vertex& i_dst) override;
    void set_edge(int i_src, int i_dst) override;
    bool is_grpah_strongly_connected();
    directed_graph* get_transposed();
    bool all_degrees_equal();
    list<vertex> &get_ending_list() { return ending_list; }
    void mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex) override;
    graph* get_dummy_graph() override;
    bool is_connected() override;
    vector<pair<int, int>> find_bridges() override;
    directed_graph* get_directed_graph(list<vertex>& ending_list) override { return this;}
};