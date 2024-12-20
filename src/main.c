#include "../inc/lem_in.h"

t_net	**catch()
{
	static t_net	*net;

	return(&net);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(-1);
	input_parser(argv[1]);
	prune_orphans();
	deactivate_ends();
	tectonics();
	prune_subnets();
	print_net();
	return (0);
}
