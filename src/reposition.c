#include "../inc/lem_in.h"

void	sim(bool i)
{
	t_net	*net;

	net = *catch();
	if (i)
		plot_graph(color_by_distance);

	velocity_reset();
	force_reset();
	printf ("%i\n", i);
	repulsion();
	attraction();
	apply_forces();
}

int	main(int argc, char **argv, char **env)
{
	t_net	*net;
	t_vec2d	diagonal;

	if (argc != 2)
		exit(-1);

	input_parser(argv[1]);
	srand(time(NULL));
	ft_set_pool_size(sizeof(t_qt_node), 128);

	net = *catch();
	set_distances(net->start, 0, 1);
	determine_max_coordinates();
	jitter_positions();
	velocity_reset();

	diagonal = connect2d(net->start->pos, net->end->pos);
	net->ideal_node_distance = veclen2d(&diagonal) / 3;
	corner_important();
	for (int i = 0; i < 200; i++)
	{
		sim(!(i % 10));
	}

	visualize_net();

	return (0);
}
