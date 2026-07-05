#include "../inc/lem_in.h"

void	graph_to_file(t_graph *graph, int fd)
{
	t_vec2d	p;

	if (fd < 0)
		return ;
	p = point_on_image(graph->pos);
		ft_putstr_fd(graph->name, fd);
	ft_putstr_fd(" ", fd);
	ft_putfloat_fd(fd, p.x, 4);
	ft_putstr_fd(" ", fd);
	ft_putfloat_fd(fd, p.y, 4);
	ft_putstr_fd("\n", fd);
}

void	link_to_file(t_link *link, int fd)
{
	if (fd < 0)
		return ;
	ft_putstr_fd(link->from->name, fd);
	ft_putstr_fd("-", fd);
	ft_putstr_fd(link->to->name, fd);
	ft_putstr_fd("\n", fd);
}

char	*out_name(char *file)
{
	char	**parts;
	int		i;
	char	*new_file;
	int		l;

	parts = ft_split(file, '/');
	new_file = ft_calloc(ft_strlen(file) + 8, sizeof(char));
	i = 0;
	while (parts[i])
	{
		if (parts[i + 1] == NULL)
			ft_memmove(new_file + ft_strlen(new_file), "better_", 7);
		ft_memmove(new_file + ft_strlen(new_file), parts[i], ft_strlen(parts[i]));
		if (parts[i + 1] != NULL)
			new_file[ft_strlen(new_file)] = '/';
		i++;
	}
	return (new_file);
}

void	net_to_file(int p_fd)
{
	char	*name;
	int		fd;
	t_net	*net;
	t_list	*i;
	t_graph	*graph;
	t_link	*link;

	net = *catch();
	name = out_name(net->file);
	if (p_fd > 0)
		fd = p_fd;
	else
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH);
	if (!fd)
		return ;
	ft_putnbr_fd(net->packets, fd);
	ft_putstr_fd("\n", fd);
	if (net->lines > 0)
	{
		ft_putstr_fd("#Here is the number of lines required: ", fd);
		ft_putnbr_fd(net->lines, fd);
		ft_putstr_fd("\n", fd);
	}

	graph = net->start;
	ft_putstr_fd("##start\n", fd);
	graph_to_file(graph, fd);
	graph = net->end;
	ft_putstr_fd("##end\n", fd);
	graph_to_file(graph, fd);
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		if (graph != net->start && graph != net->end)
			graph_to_file(graph, fd);
		i = i->next;
	}
	i = net->graph_links;
	while (i)
	{
		link = i->content;
		link_to_file(link, fd);
		i = i->next;
	}
	close(fd);
}

void	print_progress(int current, int total)
{
	struct winsize	w;
	int				term_width;
	float			percentage;
	int				text_width;
	int				bar_width;
	int				filled_width;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	term_width = w.ws_col;
	percentage = ((float)current / (float)total) * 100.0;
	bar_width = term_width - 10; // non bar chars :[xxx%] [] 
	filled_width = (int)(percentage / 100 * bar_width);
	printf("\r[%3d%%] [", (int)percentage);
	for (int i = 0; i < bar_width; i++) {
		if (i < filled_width)
			printf("=");
		else
			printf(" ");
	}
	printf("]");
	fflush(stdout);
}
