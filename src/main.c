#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));

	read_data(&data);
	remove_deadend(&data);

	first_level(&data);

	// level_sort(&data);

	print_nodes(data.graph);
	free_globe(&data);
	return (0);
}
