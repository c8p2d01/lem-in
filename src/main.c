#include "../inc/lem_in.h"

int	main(int argc, char **argv, char **env)
{
	t_net	*net;
	t_list	*i;
	size_t	s;

	if (argc != 2)
		exit(-1);
	input_parser(argv[1]);
	net = *catch();
	isolate_endings();
	identify_nets();
	set_distances(net->start, 0, 1);
	i = net->start->links;
	while (i)
	{
		trace_path();
		reset_distances();
		set_distances(net->start, 0, 1);
		i = i->next;
	}
	prepare_pathing();
	map_paths();
	sort_paths();
	calculate_packets();
	if (net->display)
		print_paths();
	s = 1;
	while (s)
	{
		s = send_packets();
		plot_graph(color_by_ant);
	}
	visualize_net();
	return (0);
}
