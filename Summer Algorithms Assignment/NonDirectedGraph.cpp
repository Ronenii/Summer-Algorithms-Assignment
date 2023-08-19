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

    return is_all_black();
}

// A dfs visit with a modification that directs the edges according to the dfs run direction. Sets the directed edge in 'i_directed_graph'
// We run with DFS on the non directed graph and modify the given directed graph.
// We also keep an ending list of the vertices in the order they were visited.
void non_directed_graph::visit_and_direct(vertex& i_vertex, graph& i_directed_graph, list<vertex>& ending_list, int parent)
{
    const list<vertex>& neighbors = i_vertex.get_neighbors();

    if (i_vertex.get_color() == Color::WHITE)
    {
        i_vertex.set_color(Color::GRAY);

        // make the vertex gray in the directed graph
        vertex& in_directed_graph = i_directed_graph.get_real_nighbor(i_vertex);
        in_directed_graph.set_color(Color::GRAY);

        for (const vertex& v : neighbors)
        {
            vertex& real_neighbor = m_vertexes[v.get_value() - 1];

             if (real_neighbor.get_color() == Color::WHITE)
             {
                i_directed_graph.set_edge(i_vertex.get_value(), real_neighbor.get_value());
                visit_and_direct(real_neighbor, i_directed_graph, ending_list, i_vertex.get_value());
             }
             else if(real_neighbor.get_value() != parent && real_neighbor.get_color() == Color::GRAY){
                    i_directed_graph.set_edge(i_vertex.get_value(), real_neighbor.get_value());
             }

        }

        i_vertex.set_color(Color::BLACK);

        // make the vertex black in the directed graph
        in_directed_graph.set_color(Color::BLACK);

        // add the vertex to the ending list as neutral
        i_vertex.set_color(Color::WHITE);
        ending_list.push_back(i_vertex);
        i_vertex.set_color(Color::BLACK);
    }
}


vector<pair<int, int>> non_directed_graph::find_bridges()
{
    // The idea is to run DFS, the transpose the graph and run DFS again while keeping track of the parents' vertex.
    // If the parent vertex is not the same as the vertex we started from, then we have a bridge.

    vector<pair<int, int>> bridges;
    list<vertex> ending_list;

    graph* dg = get_directed_graph(ending_list);
    dg->set_all_white();

    directed_graph* dgt = dynamic_cast<directed_graph*>(dg)->get_transposed();
    dgt->set_all_white();

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
        vertex& real_entry_vertex = this->m_vertexes[entry_vertex_value - 1];

        if(real_entry_vertex.get_color() == Color::BLACK){

            // This means we have already been to this vetex and marked it with a representative.
            // So we just need to update the vetex in the transposed graph.
            transposed_graph->get_vertex_by_value(entry_vertex_value) = real_entry_vertex;

            ending_list.pop_back();
            continue;
        }

        visit_and_mark_rep(transposed_graph->get_vertex_by_value(entry_vertex_value), entry_vertex_value);
        ending_list.pop_back();
    }
}

// A DFS visit with a modification that marks each vertex with a representative.
void non_directed_graph::visit_and_mark_rep(vertex& i_vertex, const int rep)
{
    vertex &in = get_real_nighbor(i_vertex);

    // if the vertex has no rep, set it to be the rep. This means it's the first time we see it.
    if( in.get_rep() == -1) {
        i_vertex.set_rep(rep);
        in.set_rep(rep);
    }

    const list<vertex>& neighbors = i_vertex.get_neighbors();

    if (in.get_color() == Color::WHITE)
    {
        i_vertex.set_color(Color::GRAY);
        in.set_color(Color::GRAY);

        for (const vertex& v : neighbors)
        {
            vertex& real_neighbor = m_vertexes[v.get_value() - 1];
            if (real_neighbor.get_color() == Color::WHITE)
            {
                visit_and_mark_rep(real_neighbor, rep);
            }
        }
        i_vertex.set_color(Color::BLACK);
        in.set_color(Color::BLACK);
    }
}


// Returns a directed graph from this non directed graph using a DFS run.
directed_graph* non_directed_graph::get_directed_graph(list<vertex>& ending_list) {
    set_all_white();
    directed_graph* directed = new directed_graph(m_num_of_vertexes, m_num_of_edges);
    vector<vertex> my_vertexes = get_vertexes();

    for (vertex & v : my_vertexes)
    {
        vertex& real_vertex = m_vertexes[v.get_value() - 1];
        visit_and_direct(real_vertex, *directed, ending_list, -1);
    }

    return directed;
}

//
void non_directed_graph::set_edge(int i_src, int i_dst) {
    set_edge(m_vertexes[i_src], m_vertexes[i_dst]);
}

//bool dfs(int curr, int des, vector<vector<int> >& adj,
//         vector<int>& vis)
//{
//
//    // If curr node is destination return true
//    if (curr == des) {
//        return true;
//    }
//    vis[curr] = 1;
//    for (auto x : adj[curr]) {
//        if (!vis[x]) {
//            if (dfs(x, des, adj, vis)) {
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//bool isPath(int src, int des, vector<vector<int> >& adj)
//{
//    vector<int> vis(adj.size() + 1, 0);
//    return dfs(src, des, adj, vis);
//}
//
//vector<vector<int>> non_directed_graph::stronglyConnectedComponents() {
//
//    // Stores all the strongly connected components.
//    vector<vector<int> > ans;
//
//    // Stores whether a vertex is a part of any Strongly
//    // Connected Component
//    vector<int> is_scc(n + 1, 0);
//
//    vector<vector<int> > adj(n + 1);
//
//    for (int i = 0; i < a.size(); i++) {
//        adj[a[i][0]].push_back(a[i][1]);
//    }
//
//    // Traversing all the vertices
//    for (int i = 1; i <= n; i++) {
//
//        if (!is_scc[i]) {
//
//            // If a vertex i is not a part of any SCC
//            // insert it into a new SCC list and check
//            // for other vertices whether they can be
//            // thr part of thidl ist.
//            vector<int> scc;
//            scc.push_back(i);
//
//            for (int j = i + 1; j <= n; j++) {
//
//                // If there is a path from vertex i to
//                // vertex j and vice versa put vertex j
//                // into the current SCC list.
//                if (!is_scc[j] && isPath(i, j, adj)
//                    && isPath(j, i, adj)) {
//                    is_scc[j] = 1;
//                    scc.push_back(j);
//                }
//            }
//
//            // Insert the SCC containing vertex i into
//            // the final list.
//            ans.push_back(scc);
//        }
//    }
//    return ans;
//
//}

//vector<vertex> non_directed_graph::transpose(vector<vertex>& i_vertexes) {
//
//    int numVertices = i_vertexes.size();
//    vector<vertex> transposedGraph(numVertices);
//
//
//    for (int i = 0; i < numVertices; i++) {
//        transposedGraph[i].set_value(i_vertexes[i].get_value());
//    }
//
//    for (int i = 0; i < numVertices; i++) {
//        vertex v = i_vertexes[i];
//        list<vertex> neighbors = v.get_neighbors();
//        for (const auto& neighbor : neighbors) {
//            transposedGraph[neighbor.get_value() - 1].add_neighbor(v);
//            cout << "Adding neighbor " << v.get_value() << " to " << neighbor.get_value() << endl;
//        }
//    }
//
//    return transposedGraph;
//}

