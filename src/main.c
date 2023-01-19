#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));
	readData(&data);

	add_level(&data);
	delete_useless_node(&data);
	unlink_same_level(&data);
	delete_deadend(&data);
	sort_level(&data);
	remove_input_links(&data);
	remove_output_links(&data);
	find_all_shortest_paths(&data);

	print_nodes(data.allNodes);
	print_paths(&data);

	freeGlobe(&data);
}
