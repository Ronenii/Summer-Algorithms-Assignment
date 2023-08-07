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
//	i_current_vertex.get_neighbors().remove(i_neighbor_vertex);
//	i_neighbor_vertex.get_neighbors().remove(i_current_vertex);
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


bool non_directed_graph::is_euler()
{
    if (!is_connected())
        return false;
    return is_even_degrees();
}

bool non_directed_graph::is_directed()
{
    return false;
}

bool non_directed_graph::is_connected()
{
    set_all_white();
    visit(m_vertexes[0]);
    return is_all_black();
}


graph* non_directed_graph::dfs(vertex& i_vertex)
{

}


vector<vertex> non_directed_graph::find_bridges()
{
    vector<vertex> bridges;

    // We will use the DFS algorithm to find bridges.
    // We will start from the first vertex in the graph.
    // We will mark the vertex as visited and then we will go over all of its neighbors.
    // If the neighbor is white, we will mark it as visited and then we will call the DFS algorithm recursively.
    // If the neighbor is black, we will skip it.
    
//    for(auto vertex : m_vertexes)
//    {
//        if(vertex.get_color() == Color::WHITE)
//        {
//            visit(vertex);
//
//        }
//    }
    return bridges;
}