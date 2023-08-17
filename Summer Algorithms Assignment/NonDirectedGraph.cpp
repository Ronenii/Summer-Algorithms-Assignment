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

    //make empty graph
//    graph* directed = get_dummy_graph();
//    visit_and_direct(m_vertexes[0], *directed);

    return is_all_black();
}

// A dfs visit with a modification that directs the edges according to the dfs run direction. Sets the directed edge in 'i_directed_graph'
// We run with DFS on the non directed graph and modify the given directed graph.
//
// TODO: Add parent field and adjust set edge to always set an edge between vertices unless its an edge to a prev.
void non_directed_graph::visit_and_direct(vertex& i_vertex, graph& i_directed_graph, list<vertex>& ending_list)
{
    const list<vertex>& neighbors = i_vertex.get_neighbors();

    if (i_vertex.get_color() == Color::WHITE)
    {
        i_vertex.set_color(Color::GRAY);
        for (const vertex& v : neighbors)
        {
            vertex& real_neighbor = m_vertexes[v.get_value() - 1];
            if (real_neighbor.get_color() == Color::WHITE)
            {
                i_directed_graph.set_edge(i_vertex.get_value(), real_neighbor.get_value());
                visit_and_direct(real_neighbor, i_directed_graph, ending_list);
            }
        }
        i_vertex.set_color(Color::BLACK);
        ending_list.push_back(i_vertex);
    }
}


vector<pair<int, int>> non_directed_graph::find_bridges()
{
    // The idea is to run DFS, the transpose the graph and run DFS again while keeping track of the parents' vertex.
    // If the parent vertex is not the same as the vertex we started from, then we have a bridge.

    vector<pair<int, int>> bridges;
    list<vertex> ending_list;

    graph* dg = get_directed_graph(ending_list);

    directed_graph* dgt = dynamic_cast<directed_graph*>(dg)->get_transposed();

    DFS_on_transposed_with_ending_list(dgt, ending_list);

    vector<vertex> my_vertexes = dg->get_vertexes();


    for (vertex & v : my_vertexes)
    {
        list<vertex> my_neighbors = v.get_neighbors();
        for (vertex & my_neighbor : my_neighbors)
        {
            vertex& current = dgt->get_vertex_by_value(v.get_value());
            vertex& neighbor = dgt->get_vertex_by_value(my_neighbor.get_value());

            if(current.get_rep() != neighbor.get_rep())
            {
                bridges.emplace_back(current.get_value(), neighbor.get_value());
            }
        }
    }

    return bridges;
}

// Run a DFS on the transposed graph according to the ending list.
// Each visit will mark a strongly connected component with a representative vertex.
void non_directed_graph::DFS_on_transposed_with_ending_list(directed_graph* transposed_graph, list<vertex>& ending_list)
{
    this->set_all_white();
    while (!ending_list.empty())
    {
        int entry_vertex_value = ending_list.back().get_value();
        visit_and_mark_rep(transposed_graph->get_vertex_by_value(entry_vertex_value), entry_vertex_value);
        ending_list.pop_back();
    }
}

// A DFS visit with a modification that marks each vertex with a representative.
void non_directed_graph::visit_and_mark_rep(vertex& i_vertex, const int rep)
{
    i_vertex.set_rep(rep);
    const list<vertex>& neighbors = i_vertex.get_neighbors();

    if (i_vertex.get_color() == Color::WHITE)
    {
        i_vertex.set_color(Color::GRAY);
        for (const vertex& v : neighbors)
        {
            vertex& real_neighbor = m_vertexes[v.get_value() - 1];
            if (real_neighbor.get_color() == Color::WHITE)
            {
                visit_and_mark_rep(real_neighbor, rep);
            }
        }
        i_vertex.set_color(Color::BLACK);
    }
}



void non_directed_graph::stronglyConnectedComponents() {

    vector<vertex> transposedGraph = transpose(m_vertexes);

    // We will use the DFS algorithm to find strongly connected components.
    // We will start from the first vertex in the graph.

    for (auto vertex : m_vertexes) {
        if (vertex.get_color() == Color::WHITE) {
            visit(vertex);
        }
    }

    cout << "Hello " << endl;

}

vector<vertex> non_directed_graph::transpose(vector<vertex>& i_vertexes) {

    int numVertices = i_vertexes.size();
    vector<vertex> transposedGraph(numVertices);


    for (int i = 0; i < numVertices; i++) {
        transposedGraph[i].set_value(i_vertexes[i].get_value());
    }

    for (int i = 0; i < numVertices; i++) {
        vertex v = i_vertexes[i];
        list<vertex> neighbors = v.get_neighbors();
        for (const auto& neighbor : neighbors) {
            transposedGraph[neighbor.get_value() - 1].add_neighbor(v);
            cout << "Adding neighbor " << v.get_value() << " to " << neighbor.get_value() << endl;
        }
    }

    return transposedGraph;
}

// Returns a directed graph from this non directed graph using a DFS run.
directed_graph* non_directed_graph::get_directed_graph(list<vertex>& ending_list) {
    set_all_white();
    directed_graph* directed = new directed_graph(m_num_of_vertexes, m_num_of_edges);
    vector<vertex> my_vertexes = get_vertexes();

    for (vertex & v : my_vertexes)
    {
        visit_and_direct(v, *directed, ending_list);
    }

    return directed;
}

//
void non_directed_graph::set_edge(int i_src, int i_dst) {
    set_edge(m_vertexes[i_src], m_vertexes[i_dst]);
}