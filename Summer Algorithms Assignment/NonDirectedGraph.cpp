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

bool non_directed_graph::is_connected()
{
    set_all_white();
    visit(m_vertexes[0]);
    return is_all_black();
}

// Creates a directed graph based on a dfs run on this non directed graph
directed_graph* non_directed_graph::create_directed_graph_with_dfs()
{
    directed_graph * ret = new directed_graph(this->get_num_of_vertexes(), get_num_of_edges());
	non_directed_graph * dg = dynamic_cast<non_directed_graph*>(get_dummy_graph());

    for (vertex & v : m_vertexes)
    {
		dg->visit_and_direct(v, *ret);
    }

	delete dg;
	return ret;
}

// A dfs visit with a modification that directs the edges according to the dfs run direction. Sets the directed edge in 'i_directed_graph'
void visit_and_direct(vertex & i_vertex, graph & i_directed_graph)
{
	list<vertex> neighbors = i_vertex.get_neighbors();
	if(i_vertex.get_color() == Color::WHITE)
	{
		i_vertex.set_color(Color::GRAY);
		for (vertex& v : neighbors)
		{
			if (v.get_color() == Color::WHITE)
			{
				i_directed_graph.set_edge(i_vertex, v);
				visit_and_direct(v, i_directed_graph);
			}
		}
		i_vertex.set_color(Color::BLACK);
	}
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