#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));
	readData(&data);

	level(&data);

	level_sort(&data);

	print_nodes(data.allNodes);

	ft_g_unlink(data.start->gates[0], data.start);

	printf("\e[38;5;234m");
	print_nodes(data.allNodes);
	printf("\e[0m");

	freeGlobe(&data);
}
