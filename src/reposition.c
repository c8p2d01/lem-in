#include "../inc/lem_in.h"

int	main(int argc, char **argv, char **env)
{
	t_net	*net;
	t_list	*i;
	size_t	n;
	size_t	used_nodes;


	if (argc != 2)
		exit(-1);
	input_parser(argv[1]);
	net = *catch();
	isolate_endings();
	identify_nets();

	i = net->start->links;
	while (i)
	{
		set_distances(net->start, 0, 1);
		trace_path();
		reset_distances();
		i = i->next;
	}

	prepare_pathing();
	map_paths();

	n = 0;
	used_nodes = 0;
	while (n < net->n_paths)
	{
		if (ft_lstsize(net->paths[n].path_nodes) > used_nodes)
			used_nodes = ft_lstsize(net->paths[n].path_nodes);
		n++;
	}

	net->ideal_node_distance = WDTH / 2 / used_nodes;

	jitter_positions();
	scale_positions();

	animate(1, 600, 10);

	visualize_net();

	//int total = 250;
    //for (int i = 0; i <= total; i++) {
    //    print_progress(i, total);
    //    usleep(50000); // 50 Millisekunden warten
    //}
    //printf("\n");

	return (0);
}
