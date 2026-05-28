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
	plot_graph(color_by_distance);
	srand(time(NULL));
	for (int i = 0; net->simulate && i < 360; i++)
	{
		calculate_forces();
		heat = apply_forces();
		//if (!(i % 100))
		//	printf("heat : %lf\n", heat);
		//if (!(i % 100))
		//	plot_graph(color_by_distance);
		//corner_imprtant();
	}
	trim_net();
	prepare_pathing();
	map_paths();
	print_paths();
	//send_off();
	//print_paths();
	//#ifdef BONUS
	//	assignColorToPath(env);
	//	bonus();
	//#endif
	visualize_net();
	return (0);
}
