#include "../inc/lem_in.h"

#include <fcntl.h>

int main()
{

	globe data;
	ft_bzero(&data, sizeof(globe));

	openat(3, "/Users/vheymans/Documents/code/github/lem-in/map/test.map", O_RDONLY);
	read_data(&data);

	close(3);

	remove_deadend(&data);

	first_level(&data);
	first_flow(data.end, &data);
	int i = 1;
	printf("%d------\n",i);
	leveling(&data);
	//print_nodes(data.graph);
	//after_flow(data.end, &data);
	while (after_flow(data.end, &data) && i < 10)
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

	ant_march(&data);

	free_globe(&data);
	return (0);
}
