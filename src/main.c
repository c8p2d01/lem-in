#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));
	readData(&data);

	level(&data);

	level_sort(&data);

	print_nodes(data.allNodes);

	printf("\e[38;5;196m");
	print_nodes(data.allNodes);
	printf("\e[0m");

	freeGlobe(&data);
}
