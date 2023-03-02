#include "../inc/lem_in.h"

#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	globe data;
	ft_bzero(&data, sizeof(globe));

	openat(3, "/Users/cdahlhof/Documents/lem-in/test", O_RDONLY);
	read_data(&data);

	close(3);
	printf("something1\n");

	remove_deadend(&data);
	printf("something1\n");

	first_level(&data);
	if (data.end->first_lvl != -1)
	{
		int i = 1;
		first_flow(data.end, &data);
		printf("%d------\n",i);
		
		leveling(&data);
		while (after_flow(data.end, &data, false))
		{
			if (data.end->after_lvl == -1)
				break;
			i++;
			printf("%d------\n",i);
			dry(data.graph);
			leveling(&data);
		}

		print_nodes(data.graph);

		 data.paths = cartograph(&data);
		 printf("done cartography\n");

		path_sort(&data);
		for (int i = 0; data.paths[i]; i ++)
			mapper(data.paths[i]);
		printf("done sorter\n");


		// // for the tester
		 printf("TESTER:%s\n", data.end->name);

		 ant_march(&data);

		bonus(&data, env);
		(void)env;
	}
	else
		printf("no connection between start and end found\n");
	// free_globe(&data);
	return (0);
}
