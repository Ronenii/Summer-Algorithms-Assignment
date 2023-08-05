#include "NonDirectedGraph.h"

void non_directed_graph::set_edge(vertex& i_src, vertex& i_dst)
{
	i_src.add_neighbor(i_dst);
	i_src.set_degree(i_src.get_degree() + 1);
	i_dst.add_neighbor(i_src);
	i_dst.set_degree(i_dst.get_degree() + 1);
}

void non_directed_graph::mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex)
{
	i_current_vertex.get_neighbors().remove(i_neighbor_vertex);
	i_neighbor_vertex.get_neighbors().remove(i_current_vertex);
}

bool non_directed_graph::is_even_degrees()
{
	for (auto& vertex : m_vertexes)
	{
		if (vertex.get_degree() % 2 != 0)
			return false;
	}
	return true;
}

graph* non_directed_graph::get_dummy_graph()
{
	graph* dummy_graph = new non_directed_graph(*this);
	return dummy_graph;
}


