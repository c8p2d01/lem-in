#include "../inc/lem_in.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 2)
		exit(-1);
	input_parser(argv[1]);
	isolate_endings();
	//prune_subnets();
	t_net	*net;
	net = *catch();
	set_distances();
	trace_path();
	reset_distances();
	visualize_net();
	//while (((t_content *)net->end->content)->level != 0)
	//{
	//	flow();
	//	flatten();
	//	tectonics();
	//}
	//net->pathed = true;
	//drain();
	//tectonics();
	//while (((t_content *)net->end->content)->level != 0)
	//{
	//	flow();
	//	flatten();
	//	tectonics();
	//}
	//send_off();
	//print_paths();
	//#ifdef BONUS
	//	assignColorToPath(env);
	//	bonus();
	//#endif
	return (0);
}
