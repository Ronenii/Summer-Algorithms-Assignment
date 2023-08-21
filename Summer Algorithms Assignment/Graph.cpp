#include "Graph.h"

// Initializes a graph with the given number of vertices.
graph::graph(int i_num_of_vertices, int i_num_of_edges) : m_num_of_vertices(i_num_of_vertices), m_num_of_edges(i_num_of_edges)
{
	for (int i = 0; i < i_num_of_vertices; i++)
	{
		m_vertexes.push_back(vertex(i + 1));
	}
}

// Set all vertices to be white
void graph::set_all_white()
{
	for (auto& vertex : m_vertexes)
		vertex.set_color(Color::WHITE);
}

// Returns if all of the graphs vertices are black
bool graph::is_all_black()
{
	for (auto& vertex : m_vertexes)
	{
		if (vertex.get_color() != Color::BLACK)
			return false;
	}
	return true;
}

// The visit method as described in the book
// We make a copy of the given vertex neighbors and travel along this "dummy graph" of the neighbors.
// None the changes we make (like deleting a neighbor in mark_edge) take place on the real graph.
// This also directs the graph edges according to the dfs run direction.
void graph::visit(vertex& i_vertex)
{
	list<vertex> neighbors = i_vertex.get_neighbors();
	i_vertex.set_color(Color::GRAY);
	for (auto& neighbor : neighbors)
	{
		vertex& real_neighbor = m_vertexes[neighbor.get_value() - 1];
        if(real_neighbor.get_color() != Color::WHITE){
            continue;
        }

        // We want to make the graph directed, so we delete the edge from the neighbor to the current vertex
        real_neighbor.get_neighbors().remove(i_vertex);

        // mark the parent of the neighbor
        // This is for the purpose of finding the SCC later
        real_neighbor.set_rep(i_vertex);

		visit(real_neighbor);
	}
	i_vertex.set_color(Color::BLACK);
}