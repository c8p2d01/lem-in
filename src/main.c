#include "../inc/lem_in.h"

#include <fcntl.h>

int main()
{

	globe data;
	ft_bzero(&data, sizeof(globe));

	openat(3, "/Users/cdahlhof/Documents/lem-in/map/ex3", O_RDONLY);

	read_data(&data);

	remove_deadend(&data);

	first_level(&data);
	printf("\ndebug %i\n", 42);
	first_flow(data.end, &data);
	int i = 1;
	printf("%d------\n",i);
	leveling(&data);
	//print_nodes(data.graph);
	//after_flow(data.end, &data);
	while (after_flow(data.end, &data))
	{
		i ++;
		printf("%d------\n",i);
		leveling(&data);
		//print_nodes(data.graph);
		
	}


	// path_diver
	// ant_coordination

	print_nodes(data.graph);
	free_globe(&data);
	return (0);
}
