#pragma once

#include  <list>
#include <vector>

using namespace std;
enum class Color { WHITE, GRAY, BLACK };

class vertex
{
private:
	int m_in_degree = 0, m_out_degree = 0, m_degree = 0;
	int m_value;
	Color m_color = Color::WHITE;
	list<vertex> m_neighbors; // change to by value.
public:
	vertex(int i_value = 0) { m_value = i_value; }
	~vertex() = default;
	void add_neighbor(vertex& i_neighbor);
	bool neighbor_exists(const vertex& i_neighbor) const;
	list<vertex>& get_neighbors() { return m_neighbors; }
	int get_value()const { return m_value; }
	void set_value(int i_value) { m_value = i_value; }
	bool operator==(const vertex& i_other)const { return i_other.m_value == m_value; }
	void set_degree(int i_degree) { m_degree = i_degree; }
	int get_degree() const { return m_degree; }
	int get_in_degree() const { return  m_in_degree; }
	void set_in_degree(int i_in_degree) { m_in_degree = i_in_degree; }
	int get_out_degree() const { return  m_out_degree; }
	void set_out_degree(int i_out_degree) { m_out_degree = i_out_degree; }
	void set_color(Color i_color) { m_color = i_color; }
	Color get_color() const { return m_color; }
	bool has_neighbors();
	static vertex& get_vertex_from_circuit(list<vertex*>& i_circuit, int i_index);
	static void paste_circuit(list<vertex*>& i_dst, list<vertex*>& i_src, int i_start_index);
};