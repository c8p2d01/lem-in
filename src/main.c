#include "../inc/lem_in.h"

#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
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
	for (int i = 0; data.paths[i]; i ++)
		mapper(data.paths[i]);
	printf("done sorter\n");

	/*mapper(data.paths[0]);
	mapper(data.paths[1]);*/


	// for the tester
	printf("TESTER:%s\n", data.end->name);
	printf("shortest path len: %zu \t\t longest: %zu\n", data.paths[0]->len, data.paths[3]->len);

	ant_march(&data);

	bonus(&data, env);

	free_globe(&data);
	return (0);
}
