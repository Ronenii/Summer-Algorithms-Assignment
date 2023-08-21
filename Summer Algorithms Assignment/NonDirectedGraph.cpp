#include "NonDirectedGraph.h"

// Set edges in non directed graph
void non_directed_graph::set_edge(vertex& i_src, vertex& i_dst)
{
    i_src.add_neighbor(i_dst);
    i_dst.add_neighbor(i_src);
}

void non_directed_graph::mark_edge(vertex& i_current_vertex, vertex& i_neighbor_vertex)
{
    	i_current_vertex.get_neighbors().remove(i_neighbor_vertex);
    	i_neighbor_vertex.get_neighbors().remove(i_current_vertex);
}

graph* non_directed_graph::get_dummy_graph()
{
    graph* dummy_graph = new non_directed_graph(*this);
    return dummy_graph;
}

// Check if the graph is connected - if we can reach all the vertexes from the first vertex
bool non_directed_graph::is_connected()
{
    set_all_white();
    visit(m_vertexes[0]);

    return is_all_black();
}
// Transposing the directed graph and doing DFS on it from the ending list
bool non_directed_graph::edge_exists(const int i_src, const int i_dst)
{
    return get_vertex_by_id(i_src).neighbor_exists(get_vertex_by_id(i_dst));
}

// A dfs visit with a modification that directs the edges according to the dfs run direction. Sets the directed edge in 'i_directed_graph'
// We run with DFS on the non directed graph and modify the given directed graph.
// We also keep an ending list of the vertices in the order they were visited.
void non_directed_graph::visit_and_direct(vertex& i_vertex, graph& i_directed_graph, list<vertex>& ending_list, const int parent)
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
                visit_and_direct(real_neighbor, i_directed_graph, ending_list, i_vertex.get_value());
             }
             else if(real_neighbor.get_value() != parent && !i_directed_graph.edge_exists(real_neighbor.get_value(), i_vertex.get_value())){
                    i_directed_graph.set_edge(i_vertex.get_value(), real_neighbor.get_value());
             }

        }

        // Add the vertex to the ending list as neutral
        ending_list.push_back(i_vertex);
        i_vertex.set_color(Color::BLACK);
    }
}


vector<pair<int, int>> non_directed_graph::find_bridges(vector<pair<int, int>> i_edges)
{
    // The idea is to run DFS, the transpose the graph and run DFS again while keeping track of the parents' vertex.
    // If the parent vertex is not the same as the vertex we started from, then we have a bridge.

    vector<pair<int, int>> bridges; // Will hold the bridges
    list<vertex> ending_list;
    
    // Get the directed graph and the ending list from the input graph
    graph* dg = get_directed_graph(ending_list);
    dg->set_all_white();
    
    directed_graph* dgt = dynamic_cast<directed_graph*>(dg)->get_transposed();
    dgt->set_all_white();

    mark_strongly_connected_components(dgt, ending_list);

    vector<vertex> my_vertexes = dg->get_vertexes();

    return scan_for_bridges(*dgt,i_edges );
}

// Iterates over all edges in the directed transposed graph (after its stogrly connected components are marked)
// Adds an edge to the bridge list if the edge has 2 vertices of with different reps.
vector<pair<int, int>>& non_directed_graph::scan_for_bridges(directed_graph& directed_graph_transposed,
                                                             const vector<pair<int, int>>& i_edges)
{
    vector<pair<int, int>>* bridges = new vector<pair<int, int>>();

    for (const pair<int, int> & p : i_edges)
    {
        vertex& end1 = directed_graph_transposed.get_vertex_by_id(p.first);
        vertex& end2 = directed_graph_transposed.get_vertex_by_id(p.second);
	    if(end1.get_rep() != end2.get_rep())
	    {
            bridges->emplace_back(end1.get_value(), end2.get_value());
	    }
    }

    return *bridges;
}

// Run a DFS on the transposed graph according to the ending list.
// Each visit will mark a strongly connected component with a representative vertex.
void non_directed_graph::mark_strongly_connected_components(directed_graph* transposed_graph, list<vertex>& ending_list)
{
    this->set_all_white();
    while (!ending_list.empty())
    {
        int entry_vertex_value = ending_list.back().get_value();
        vertex& real_entry_vertex = this->m_vertexes[entry_vertex_value - 1];

        if(real_entry_vertex.get_color() == Color::BLACK){

            // This means we have already been to this vertex and marked it with a representative.
            // So we just need to update the vertex in the transposed graph.
            transposed_graph->get_vertex_by_id(entry_vertex_value) = real_entry_vertex;

            ending_list.pop_back();
            continue;
        }

        transposed_graph->visit_and_mark_rep(transposed_graph->get_vertex_by_id(entry_vertex_value), entry_vertex_value);
        ending_list.pop_back();
    }
}


// Returns a directed graph from this non directed graph using a DFS run.
directed_graph* non_directed_graph::get_directed_graph(list<vertex>& ending_list) {
    set_all_white();
    directed_graph* directed = new directed_graph(m_num_of_vertices, m_num_of_edges);
    vector<vertex> my_vertexes = get_vertexes();

    for (vertex & v : my_vertexes)
    {
        vertex& real_vertex = m_vertexes[v.get_value() - 1];
        visit_and_direct(real_vertex, *directed, ending_list, -1);
    }

    // This is done because all edges are added as black to the ending list.
    set_ending_list_white(ending_list);
    
    return directed;
}

// Setting the ending list's vertexes to white
void non_directed_graph::set_ending_list_white(list<vertex>& ending_list)
{
	for (vertex & v : ending_list)
	{
        v.set_color(Color::WHITE);
	}
}

void non_directed_graph::set_edge(const int i_src, const int i_dst) {
    set_edge(m_vertexes[i_src], m_vertexes[i_dst]);
}
