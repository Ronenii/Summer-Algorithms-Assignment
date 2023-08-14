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
void non_directed_graph::visit_and_direct(vertex & i_vertex, graph & i_directed_graph)
{
	list<vertex>& neighbors = i_vertex.get_neighbors();

	if(i_vertex.get_color() == Color::WHITE)
	{
		i_vertex.set_color(Color::GRAY);
		for (vertex& v : neighbors)
		{
			if (v.get_color() == Color::WHITE)
			{
                i_directed_graph.set_edge(i_vertex.get_value(), v.get_value());
				visit_and_direct(v, i_directed_graph);
			}
		}
		i_vertex.set_color(Color::BLACK);
	}
}


vector<vertex> non_directed_graph::find_bridges()
{
    // The idea is to run DFS, the transpose the graph and run DFS again while keeping track of the parents' vertex.
    // If the parent vertex is not the same as the vertex we started from, then we have a bridge.

    vector<vertex> bridges;

    // We will use the DFS algorithm to find bridges.
    for (auto vertex : m_vertexes) {
        if (vertex.get_color() == Color::WHITE) {
            visit(vertex);
        }
    }

    vector<vertex> transposedGraph = transpose(m_vertexes);

    // We will use the DFS algorithm to find bridges.
    for (auto vertex : transposedGraph) {
        if (vertex.get_color() == Color::WHITE) {
            visit(vertex);
        }
    }

    // TODO : Check if the parent is not the same as the vertex we started from.
    for (auto& vertex : m_vertexes) {
        for(auto& neighbor : vertex.get_neighbors()) {
            if (neighbor.get_rep() != vertex.get_value()) {
                bridges.push_back(vertex);
            }
        }
    }
    return bridges;
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

vector<vertex> non_directed_graph::transpose(vector<vertex> &i_vertexes) {

    int numVertices = i_vertexes.size();
    vector<vertex> transposedGraph(numVertices);


    for(int i = 0; i < numVertices; i++) {
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

graph *non_directed_graph::get_directed_graph() {
    graph* directed = new directed_graph(m_num_of_vertexes, m_num_of_edges);
    visit_and_direct(m_vertexes[0], *directed);
    return directed;
}

void non_directed_graph::set_edge(int i_src, int i_dst) {
    set_edge(m_vertexes[i_src], m_vertexes[i_dst]);
}
