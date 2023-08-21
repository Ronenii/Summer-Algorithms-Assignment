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
    int m_parent = -1;
    int m_rep = -1;
	list<vertex> m_neighbors; // List of neighbors
public:
	vertex(int i_value = 0) { m_value = i_value;}
	~vertex() = default;
	void add_neighbor(const vertex& i_neighbor);
	bool neighbor_exists(const vertex& i_neighbor) const;
	list<vertex>& get_neighbors() { return m_neighbors; }
	int get_value()const { return m_value; }
	bool operator==(const vertex& i_other)const { return i_other.m_value == m_value; }
	void set_degree(const int i_degree) { m_degree = i_degree; }
	int get_degree() const { return m_degree; }
	int get_in_degree() const { return  m_in_degree; }
	void set_in_degree(const int i_in_degree) { m_in_degree = i_in_degree; }
	int get_out_degree() const { return  m_out_degree; }
	void set_out_degree(const int i_out_degree) { m_out_degree = i_out_degree; }
	void set_color(const Color i_color) { m_color = i_color; }
	Color get_color() const { return m_color; }
    int get_parent() const { return m_parent;}
    void set_parent(const int i_parent) { m_parent = i_parent; }
    void set_rep(const vertex &i_vertex);
	int get_rep() const { return m_rep;}
	void set_rep(const int i_parent) { m_rep = i_parent; }
};