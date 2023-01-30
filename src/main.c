#include "../inc/lem_in.h"

#include <fcntl.h>

int main()
{

	globe data;
	ft_bzero(&data, sizeof(globe));

	openat(3, "/Users/cdahlhof/Documents/lem-in/map/ex3", O_RDONLY);

	read_data(&data);

	close(3);

	remove_deadend(&data);

	first_level(&data);
	first_flow(data.end, &data);
	int i = 1;
	printf("%d------\n",i);
	leveling(&data);
	while (after_flow(data.end, &data))
	{
		i++;
		printf("%d------\n",i);
		leveling(&data);
	}

	print_nodes(data.graph);

	data.paths = cartograph(&data);

	path_sort(&data);

	ant_march(&data);

	free_globe(&data);
	return (0);
}
