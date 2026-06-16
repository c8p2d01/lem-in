#include "../inc/lem_in.h"

int	main(int argc, char **argv, char **env)
{
	t_net	*net;
	t_list	*i;
	double	heat;

	if (argc != 2)
		exit(-1);
	input_parser(argv[1]);
	net = *catch();
	isolate_endings();
	identify_nets();
	plot_graph(color_by_path);
	set_distances(net->start, 0, 1);

	srand(time(NULL));

	jitter_positions();
	force_reset();
	velocity_reset();

	plot_graph(color_by_distance);
	calculate_forces();
	plot_graph(color_by_distance);

	i = net->start->links;
	while (i)
	{
		plot_graph(color_by_distance);
		trace_path();
		plot_graph(color_by_distance);
		reset_distances();
		set_distances(net->start, 0, 1);
		i = i->next;
	}
	//prepare_pathing();
	visualize_net();
	//send_off();
	//print_paths();
	//#ifdef BONUS
	//	assignColorToPath(env);
	//	bonus();
	//#endif
	return (0);
}
