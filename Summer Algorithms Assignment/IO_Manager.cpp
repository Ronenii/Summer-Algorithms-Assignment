#include "IO_Manager.h"

// Method which runs the entire program.
// The program will determine which vertexes are bridges.
void io_manager::run_program()
{
	graph* input_graph;
	input_graph = get_user_input();
	if (input_graph != nullptr)
	{
		try
		{
			int complete_edges_counter = 0;
			const vector<pair<int, int>> edges = get_graph_input(input_graph, complete_edges_counter);
			if (complete_edges_counter == input_graph->get_num_of_edges())
			{
				const vector<pair<int, int>> bridges = input_graph->find_bridges(edges);

				if (input_graph->is_connected() == 0)
				{
					cout << "\nGraph is not connected\n";
					return;
				}

				if (bridges.empty()) {
					cout << "\nNo bridges in graph\n";
				}

				else {
					cout << "\nThe bridges are: \n";
					for (const pair<int, int>& bridge : bridges) {
						cout << bridge.first << " " << bridge.second << "\n";
					}
				}
			}
			delete(input_graph);
		}catch (invalid_input_exception& e)
		{
			cout << e.what() << endl;
		}
	}
}

// Receives user input and creates a directed or non directed graph with empty vertices based on the input.
// returns said graph.
graph* io_manager::get_user_input()
{
	try
	{
		int edges;
		int vertices;
		get_vertexes_and_edges_input(vertices, edges);
		non_directed_graph* ndg = new non_directed_graph(vertices, edges);
		return ndg;
	}
	catch (const invalid_input_exception& e)
	{
		cout << e.what() << endl;
		return nullptr;
	}

}

// User input and edge he wants to create and the method validates it.
void io_manager::get_edge_input(int& o_src, int& o_dst, const int i_num_of_vertexes)
{
	cin >> o_src >> o_dst;
	if (!(o_src > 0 && o_src <= i_num_of_vertexes) || !(o_dst > 0 && o_dst <= i_num_of_vertexes))
		throw invalid_input_exception();
}

// Receives how much edges and vertices the user wants as input and validates said input.
void io_manager::get_vertexes_and_edges_input(int& o_vertexes, int& o_edges)
{
	cin >> o_vertexes >> o_edges;
	if (!(o_vertexes > 0) || !(o_edges >= 0))
		throw invalid_input_exception();
}

// User inputs the edges he wants to create and the method validates it. User can only create the number of edges he has requested.
vector<pair<int, int>>& io_manager::get_graph_input(graph* i_graph, int& o_completed_edges)
{
	int v1, v2;
	vector<pair<int, int>>* ret = new vector<pair<int,int>>();

	for (int i = 0; i < i_graph->get_num_of_edges(); i++)
	{
		try
		{
			get_edge_input(v1, v2, i_graph->get_num_of_vertexes());
			i_graph->set_edge(i_graph->get_vertex_by_id(v1), i_graph->get_vertex_by_id(v2));
			ret->emplace_back(v1, v2);
			o_completed_edges++;
		}
		catch (const invalid_input_exception& e)
		{
			delete ret;
			throw e;
		}
	}
	return *ret;
}

