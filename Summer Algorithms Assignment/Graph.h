#pragma once
using namespace std;
#include "Vertex.h"
#include <iostream>

class directed_graph;

class graph
{
protected:
	vector<vertex> m_vertexes;
	int m_num_of_vertices, m_num_of_edges;

public:
	graph(int i_num_of_vertices, int i_num_of_edges);
	virtual ~graph() = default;
	virtual vector<vertex> get_vertexes() const { return m_vertexes; }
	virtual int get_num_of_vertexes() const { return m_num_of_vertices; }
	virtual int get_num_of_edges() const { return m_num_of_edges; }
	virtual void set_num_of_vertexes(const int i_num_of_vertexes) { m_num_of_vertexes = i_num_of_vertexes; }
	virtual void set_num_of_edges(const int i_num_of_edges) { m_num_of_edges = i_num_of_edges; }
	virtual vertex& get_vertex_by_id(int i_id) { return m_vertexes[i_id - 1]; }
	virtual void set_edge(vertex& i_src, vertex& i_dst) = 0;
    virtual void set_edge(const int i_src, const int i_dst) = 0;
    virtual directed_graph* get_directed_graph(list<vertex>& ending_list) = 0;
	void visit(vertex& i_vertex);
	void set_all_white();
	bool is_all_black();
	virtual void mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex) = 0;
	virtual bool is_connected() = 0;
	virtual graph* get_dummy_graph() = 0;
	virtual vector<pair<int, int>> find_bridges(vector<pair<int, int>> i_edges) = 0;
	virtual vertex& get_real_neighbor(vertex& i_src) = 0;
	virtual bool edge_exists(int i_src, int i_dst) = 0;
};
