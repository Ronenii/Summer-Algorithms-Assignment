#include "DirectedGraph.h"

void directed_graph::set_edge(vertex& i_src, vertex& i_dst)
{
    if (i_dst.get_parent() == -1) { // if the dst vertex has no parent meaning it's the first time we see it
        i_dst.set_parent(i_src.get_value());
    }

    i_src.add_neighbor(i_dst);
    i_src.set_out_degree(i_src.get_out_degree() + 1);
    i_dst.set_in_degree(i_dst.get_in_degree() + 1);
}

bool directed_graph::is_grpah_strongly_connected()
{
    set_all_white();
    graph* dummy_graph = get_dummy_graph();
    directed_graph* dg_transposed = dynamic_cast<directed_graph*>(dummy_graph)->get_transposed();
    dummy_graph->visit(dummy_graph->get_vertex_by_value(1));

    if(dummy_graph->is_all_black())
    {
        dg_transposed->visit(dg_transposed->get_vertex_by_value(1));
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
    directed_graph* transposed = new directed_graph(m_num_of_vertexes, m_num_of_edges);
    vertex src;
    vertex dst;

    for(auto v: m_vertexes)
    {
        vertex& dst = transposed->get_vertex_by_value(v.get_value());
        for(auto neighbor: v.get_neighbors())
        {
            vertex& src = transposed->get_vertex_by_value(neighbor.get_value());
            transposed->set_edge(src,dst);
        }
    }

    return transposed;
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

vector<pair<int, int>> directed_graph::find_bridges() {
    cout << "find_bridges() is not implemented for directed graph" << endl;

    return vector<pair<int,int>>();
}

bool directed_graph::is_connected()
{
    cout << "is_connected() is not implemented for directed graph.Only is_strongly_connected()" << endl;
    return false;
}

void directed_graph::set_edge(int i_src, int i_dst) {
    vertex& src = get_vertex_by_value(i_src);
    vertex& dst = get_vertex_by_value(i_dst);
    set_edge(src, dst);
}
