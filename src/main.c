#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));
	readData(&data);
	//establish connection()
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

	level_sort(&data);

	print_nodes(data.graph);

	ft_g_unlink(data.start->links[0], data.start);

	printf("\e[38;5;234m");
	print_nodes(data.graph);
	printf("\e[0m");

	freeGlobe(&data);
}
