#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));

	read_data(&data);
	remove_deadend(&data);

	//BFS_M(&data);

	//delete dead ends()

	//while(1)
	// {
	// 	find path based on flow then level;
	// 	BFS_M();
	// }

	// unlink all 0 flow connections
	// establith all viable paths;
	// print()

	print_nodes(data.graph);
	free_globe(&data);
	return (0);
}
