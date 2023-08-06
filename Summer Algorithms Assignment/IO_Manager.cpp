#include "IO_Manager.h"

// Method which runs the entire program.
// The program will determine which vertexes are bridges.
void io_manager::run_program()
{
	list<vertex> euler_circuit;
	graph* input_graph;
	input_graph = get_user_input();
	if (input_graph != nullptr)
	{
		int complete_edges_counter = 0;
		get_graph_input(input_graph, complete_edges_counter);
		if (complete_edges_counter == input_graph->get_num_of_edges())
		{
            // If the graph is connected, we will find the bridges.
            graph* dummy_graph = input_graph->get_dummy_graph();
            if (dummy_graph->is_connected())
            {
                input_graph->set_all_white();
                vector<vertex> bridges = input_graph->find_bridges();
                cout << "\nThe bridges are: ";
                for (vertex& bridge : bridges)
                {
                    cout << bridge.get_value() << " ";
                }
            }
            else
            {
                cout << "The graph is not connected, therefore it has no bridges." << endl;
            }
		}
		delete(input_graph);
	}
}

// Receives user input and creates a directed or non directed graph with empty vertices based on the input.
// returns said graph.
graph* io_manager::get_user_input()
{
	int vertices, edges;

	try
	{
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
void io_manager::get_edge_input(int& o_src, int& o_dst, int i_num_of_vertexes)
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
void io_manager::get_graph_input(graph* i_graph, int& o_completed_edges)
{
	int v1, v2;

	for (int i = 0; i < i_graph->get_num_of_edges(); i++)
	{
		try
		{
			get_edge_input(v1, v2, i_graph->get_num_of_vertexes());
			i_graph->set_edge(i_graph->get_vertex_by_value(v1), i_graph->get_vertex_by_value(v2));
			o_completed_edges++;
		}
		catch (const invalid_input_exception& e)
		{
			cout << e.what() << endl;
			return;
		}
	}
}

