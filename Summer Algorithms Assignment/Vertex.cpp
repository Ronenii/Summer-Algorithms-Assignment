#include "Vertex.h"

// Adds the given neighbor to the vertex's neighbor list.
void vertex::add_neighbor(vertex & i_neighbor)
{
	if (!neighbor_exists(i_neighbor))
	{
		m_neighbors.push_back(i_neighbor);
	}
}

// Checks if the given neighbor is already a neighbor of this vertex
bool vertex::neighbor_exists(const vertex& i_neighbor) const
{
	for (auto& neighbor : m_neighbors)
	{
		if (i_neighbor.m_value == neighbor.m_value)
		{
			return true;
		}
	}

	return false;
}

// Returns if the vertex has any neighbors.
bool vertex::has_neighbors()
{
	return !m_neighbors.empty();
}

////Returns the vertex @ the given index.
//vertex& vertex::get_vertex_from_circuit(list<vertex*>& i_circuit, int i_index)
//{
//	auto it = i_circuit.begin();
//	advance(it, i_index);
//	return *(*it);
//}
//
//// inserts the i_src list into the i_dst list from stating from the givern index. 
//void vertex::paste_circuit(list<vertex*>& i_dst, list<vertex*>& i_src, int i_start_index)
//{
//	i_src.pop_front();
//	auto pos = next(i_dst.begin(), i_start_index + 1);
//	i_dst.insert(pos, i_src.begin(), i_src.end());
//}