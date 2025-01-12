#include "../inc/lem_in.h"

t_net	**catch()
{
	static t_net	*net;

	return(&net);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 2)
		exit(-1);
	input_parser(argv[1]);
	prune_orphans();
	deactivate_ends();
	flatten();
	tectonics();
	prune_subnets();
	t_net	*net;
	net = *catch();
	while (((t_content *)net->end->content)->level != 0)
	{
		flow();
		flatten();
		tectonics();
	}
	net->pathed = true;
	drain();
	tectonics();
	while (((t_content *)net->end->content)->level != 0)
	{
		flow();
		flatten();
		tectonics();
	}
	send_off();
	print_paths();
	#ifdef BONUS
		assignColorToPath(env);
		bonus();
	#endif
	return (0);
}
