#include "Vertex.h"

// Adds the given neighbor to the vertex's neighbor list.
void vertex::add_neighbor(const vertex & i_neighbor)
{
	if (!neighbor_exists(i_neighbor))
	{
		m_neighbors.push_back(i_neighbor);
	}
}

// Checks if the given neighbor is already a neighbor of this vertex
bool vertex::neighbor_exists(const vertex& i_neighbor) const
{
	for(const vertex& neighbor : m_neighbors)
	{
		if (i_neighbor.m_id == neighbor.m_id)
		{
			return true;
		}
	}

	return false;
}

// Returns if the vertex has any neighbors.
bool vertex::has_neighbors() const
{
	return !m_neighbors.empty();
}

void vertex::set_rep(const vertex &i_vertex) {
    m_rep = i_vertex.m_id;
}