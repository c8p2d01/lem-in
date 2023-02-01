#include "../inc/lem_in.h"

#include <fcntl.h>

int main()
{

	globe data;
	ft_bzero(&data, sizeof(globe));

	openat(3, "/Users/vheymans/Documents/code/github/lem-in/map/tes.map", O_RDONLY);
	read_data(&data);

	close(3);
	printf("something1\n");

	remove_deadend(&data);
	printf("something1\n");

	first_level(&data);
	first_flow(data.end, &data);
	int i = 1;
	printf("%d------\n",i);
	
	leveling(&data);
	//print_nodes(data.graph);
	//print_nodes(data.graph);
	//after_flow(data.end, &data);
	while (after_flow(data.end, &data))
	{
		i++;
		printf("%d------\n",i);
		leveling(&data);
	}

	print_nodes(data.graph);

	data.paths = cartograph(&data);
	printf("done cartography\n");

	path_sort(&data);
	printf("done sorter\n");

	/*mapper(data.paths[0]);
	mapper(data.paths[1]);*/

	path_sort(&data);

	// for the tester
	printf("TESTER:%s\n", data.end->name);

	ant_march(&data);

	free_globe(&data);
	return (0);
}
