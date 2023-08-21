#include "DirectedGraph.h"

void directed_graph::set_edge(vertex& i_src, vertex& i_dst)
{
    // if the dst vertex has no parent meaning it's the first time we see it
    if (i_dst.get_parent() == -1) {
        i_dst.set_parent(i_src.get_value());
    }
    
    // Adding the edge to the graph and updating the degrees.
    i_src.add_neighbor(i_dst);
}

// Not used in this assignment.
bool directed_graph::is_graph_strongly_connected()
{
    set_all_white();
    graph* dummy_graph = get_dummy_graph();
    directed_graph* dg_transposed = dynamic_cast<directed_graph*>(dummy_graph)->get_transposed();
    dummy_graph->visit(dummy_graph->get_vertex_by_id(1));

    if(dummy_graph->is_all_black())
    {
        dg_transposed->visit(dg_transposed->get_vertex_by_id(1));
        if(dg_transposed->is_all_black())
        {
            delete(dummy_graph);
            delete(dg_transposed);
            return true;
        }
    }
    delete(dummy_graph);
    delete(dg_transposed);
    return false;
}

// We remove the neighbor so that we cant come back and visit it.
void directed_graph::mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex)
{
    i_current_vertex.get_neighbors().remove(i_neighbor_vertex);
}

// Returns the transposed version of this directed graph.
directed_graph* directed_graph::get_transposed()
{
    directed_graph* transposed = new directed_graph(m_num_of_vertices, m_num_of_edges);
    vertex src;
    vertex dst;

    for(vertex& v: m_vertexes)
    {
        vertex& dst = transposed->get_vertex_by_id(v.get_value());
        for(const vertex & neighbor: v.get_neighbors())
        {
            vertex& src = transposed->get_vertex_by_id(neighbor.get_value());
            transposed->set_edge(src,dst);
        }
    }

    return transposed;
}

// A DFS visit with a modification that marks each vertex with a representative.
void directed_graph::visit_and_mark_rep(vertex& i_vertex, const int i_rep)
{
    vertex& real_vertex = get_real_neighbor(i_vertex);

    // if the vertex has no rep, set it to be the rep. This means it's the first time we see it.
    if(real_vertex.get_rep() == -1) {
        i_vertex.set_rep(i_rep);
        real_vertex.set_rep(i_rep);
    }

    const list<vertex>& neighbors = i_vertex.get_neighbors();

    if (real_vertex.get_color() == Color::WHITE)
    {
        i_vertex.set_color(Color::GRAY);
        real_vertex.set_color(Color::GRAY);

        for (const vertex& v : neighbors)
        {
            vertex& real_neighbor = m_vertexes[v.get_value() - 1];
            if (real_neighbor.get_color() == Color::WHITE)
            {
                visit_and_mark_rep(real_neighbor, i_rep);
            }
        }
        i_vertex.set_color(Color::BLACK);
        real_vertex.set_color(Color::BLACK);
    }
}

bool directed_graph::all_degrees_equal()
{
    for(auto & v: m_vertexes)
    {
        if (v.get_in_degree() != v.get_out_degree())
        {
            return false;
        }
    }

    return true;
}

graph* directed_graph::get_dummy_graph()
{
    graph* dummy_graph = new directed_graph(*this);
    return dummy_graph;
}

vector<pair<int, int>> directed_graph::find_bridges(vector<pair<int, int>> i_edges) {
    cout << "find_bridges() is not implemented for directed graph" << endl;

    return vector<pair<int,int>>();
}

bool directed_graph::is_connected()
{
    cout << "is_connected() is not implemented for directed graph.Only is_strongly_connected()" << endl;
    return false;
}

void directed_graph::set_edge(const int i_src, const int i_dst) {
    vertex& src = get_vertex_by_id(i_src);
    vertex& dst = get_vertex_by_id(i_dst);
    set_edge(src, dst);
}

bool directed_graph::edge_exists(const int i_src, const int i_dst)
{
    return get_vertex_by_id(i_src).neighbor_exists(get_vertex_by_id(i_dst));
}
