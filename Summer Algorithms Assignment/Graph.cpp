#include "Graph.h"

// Initializes a graph with the given number of vertices.
graph::graph(int i_num_of_vertexes, int i_num_of_edges) : m_num_of_vertexes(i_num_of_vertexes), m_num_of_edges(i_num_of_edges)
{
	for (int i = 0; i < i_num_of_vertexes; i++)
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
// We make a copy of the of the given vertex neighbors and travel along this "dummy graph" of the neighbors.
// None the changes we make (like deleting a neighbor in mark_edge) take place on the real graph.
void graph::visit(vertex& i_vertex)
{
	list<vertex> neighbors = i_vertex.get_neighbors();
	i_vertex.set_color(Color::GRAY);
	for (auto& neighbor : neighbors)
	{
		vertex& real_neighbor = m_vertexes[neighbor.get_value() - 1]; //
		mark_edge(i_vertex, real_neighbor);
		visit(real_neighbor);
	}
	i_vertex.set_color(Color::BLACK);
}

//Returns a circuit in from the given vertex. Based on the algorithm in the book.
list<vertex*> graph::find_circuit(vertex& i_vertex)
{
	list<vertex*> circuit;
	vertex copy_of_neighbor, * current_vertex = &i_vertex;
	circuit.push_back(current_vertex);
	while (current_vertex->has_neighbors())
	{
		copy_of_neighbor = current_vertex->get_neighbors().front();
		vertex& real_neighbor = m_vertexes[copy_of_neighbor.get_value() - 1];
		mark_edge(*current_vertex, real_neighbor);
		circuit.push_back(&real_neighbor);
		current_vertex = &real_neighbor;
	}
	return circuit;
}

bool graph::does_vertex_exist(vertex& i_vertex) const
{
	for (auto& vertex : m_vertexes)
	{
		if (vertex == i_vertex)
			return true;
	}

	return false;
}