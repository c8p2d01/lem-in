#include "../inc/lem_in.h"

#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	globe data;
	ft_bzero(&data, sizeof(globe));

	// openat(3, "/Users/cdahlhof/Documents/lem-in/test", O_RDONLY);

	read_data(&data);

	// close(3);

	remove_deadend(&data);

	first_level(&data);
	if (data.end->first_lvl != -1)
	{
		first_flow(data.end, &data);
		
		leveling(&data);
		
		while (after_flow(data.end, &data, false, false))
		{
			dry(data.graph);
			leveling(&data);
		}

		data.paths = cartograph(&data);

		path_sort(&data);

		// for the tester
		// ft_printf("TESTER:%s\n", data.end->name);

		ant_march(&data);

		// bonus(&data, env);
		(void)env;
	}
	else
		ft_printf("Error\nno connection between start and end found\n");
	free_globe(&data);
	return (0);
}
