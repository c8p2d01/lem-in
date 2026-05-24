#include "../inc/lem_in.h"

enum INPUT {
	COMMENT = 1,
	ROOM = 2,
	LINK = 3,
	START = 4,
	END = 5
};

int8_t	determine_input_type(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 1 && line[0] == '#')
	{
		if (len > 2 && line[1] == '#')
		{
			if (!ft_strlcmp(line, "##start\n", 8))
				return (START);
			if (!ft_strlcmp(line, "##end\n", 6))
				return (END);
		}
		return (COMMENT);
	}
	if (ft_strchr(line, '-'))
		return (LINK);
	return (ROOM);
}

t_graph	*create_node(char *raw_line, t_graph **node_destination)
{
	t_net		*net;
	char **		parts;
	t_graph		*new_graph;

	net = *catch();
	parts = ft_set_split(raw_line, " \n");
	if (ft_2d_array_size((void **)parts) == 3)
	{
		if (ft_node_exist(parts[0]))
		{
			interrupt("Error: nodes with the same name : %s\n", parts[0]);
		}
		new_graph = ft_new_graph(ft_strdup(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2]));
		if (node_destination)
		{
			new_graph->important = true;
			*node_destination = new_graph;
		}
		free_2dstr(parts);
	}
	else
		interrupt("Error: node with too many or few attributes\n-->%s", raw_line);
	return (new_graph);
}

t_link	*create_link(char *raw_line)
{
	t_net		*net;
	char **		parts;
	t_link		*link;
	t_graph		*a;
	t_graph		*b;

	net = *catch();
	parts = ft_set_split(raw_line, "-\n");
	if (ft_2d_array_size((void **)parts) == 2)
	{
		a = ft_node_exist(parts[0]);
		b = ft_node_exist(parts[1]);
		free_2dstr(parts);
		if (a && b)
			link = ft_link_graphs(a, b);
		else
			interrupt("Error: nodes in link uninitialized: %s | %s\n", parts[0], parts[1]);
	}
	else
		interrupt("Error: link with too many attributes\n%s", raw_line);
	return (link);
}

void	input_check()
{
	t_net		*net;

	net = *catch();
	if (!net->start)
		interrupt("Error: no Start node has been set\n");
	if (!net->end)
		interrupt("Error: no End node has been set\n");
}

void	input_parser(char *file)
{
	int16_t		fd;
	t_net		*net;
	char *		raw_line;
	int8_t		input_type;
	t_graph		**node_destination;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(ft_printf("invalid File\n") * 0 - 1);

	net = *catch();

	node_destination = NULL;
	raw_line = get_next_line(fd);
	if (!raw_line)
		exit(ft_printf("invalid File\n") * 0 - 1);
	while (raw_line)
	{
		input_type = determine_input_type(raw_line);
		if (net->packets < 0 && input_type > COMMENT)
			net->packets = ft_atoi(raw_line);
		else if (input_type == START)
			node_destination = &net->start;
		else if (input_type == END)
			node_destination = &net->end;
		else if (input_type == ROOM)
		{
			create_node(raw_line, node_destination);
			node_destination = NULL;
		}
		else if (input_type == LINK)
			create_link(raw_line);
		ft_free(raw_line);
		raw_line = get_next_line(fd);
	}
}