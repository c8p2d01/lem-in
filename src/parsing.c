#include "../inc/lem_in.h"

enum INPUT {
	ROOM = 1,
	START = 2,
	END = 3,
	LINK = 4,
	COMMENT = 5
};

int8_t	determine_input_type(char *line)
{
	if (line[0] && line[0] == '#')
	{
		if (line[1] && line[1] == '#')
		{
			if (!ft_strncmp(line, "##start", 8))
				return (START);
			if (!ft_strncmp(line, "##end", 6))
				return (END);
		}
		return (COMMENT);
	}
	if (ft_strchr(line, '-'))
		return (LINK);
	return (ROOM);
}

void	input_parser(char *file)
{
	int16_t		fd;
	t_net		*net;
	char *		raw_line;
	char *		line;
	int8_t		input_type;
	t_graph		*new_node;


	fd = open(file, O_RDONLY);
	if (fd < 0)	{
		ft_printf("invalid File\n");
		exit(-1);
	}

	net = *catch();
	if (!net)
	{
		net = malloc(sizeof(t_net));
		*net = (t_net){
			.graph_links = NULL,
			.graph_nodes = NULL,
			.start = NULL,
			.end = NULL,
			.pathed = false,
			.paths = NULL,
			.packets = -1
		};
		*catch() = net;
	}

	raw_line = get_next_line(fd);
	if (!raw_line)
	{
		ft_printf("invalid File\n");
		exit(-1);
	}
	net->packets = ft_atoi(raw_line);
	free(raw_line);

	raw_line = get_next_line(fd);
	while (raw_line)
	{
		line  = ft_strtrim(raw_line, " \n");
		free(raw_line);
		if (!line)
			cut_loose();
		
		input_type = determine_input_type(line);
		if (input_type == COMMENT)
		{
			raw_line = get_next_line(fd);
			free(line);
			continue;
		}
		if (input_type == START)
		{
			free(line);
			raw_line = get_next_line(fd);
			line  = ft_strtrim(raw_line, " \n");
			free(raw_line);
		}
		if (input_type == END)
		{
			free(line);
			raw_line = get_next_line(fd);
			line  = ft_strtrim(raw_line, " \n");
			free(raw_line);
		}
		if (input_type == ROOM || input_type == START || input_type == END)
		{
			char **line_parts = ft_split(line, ' ');
			if (ft_2d_array_size((void **)line_parts) == 3)
			{
				t_content *c = ft_malloc(sizeof(t_content));
				*c = (t_content){
					.name = ft_strdup(line_parts[0]),
					.level = 0,
					.x = ft_atoi(line_parts[1]),
					.y = ft_atoi(line_parts[2]),
					.ant = -1,
					.path = -1
				};
				new_node = ft_malloc(sizeof(t_graph));
				*new_node = (t_graph){
					.content = c,
					.links = NULL
				};
				ft_lstadd_back(&net->graph_nodes, ft_lstnew(new_node));
				free_2dstr(line_parts);
			}
			else
			{
				free_2dstr(line_parts);
				cut_loose();
			}
			if (input_type == START)
			{
				net->start = new_node;
			}
			if (input_type == END)
			{
				net->end = new_node;
			}
		}
		else if (input_type == LINK)
		{
			char **line_parts = ft_split(line, '-');
			if (ft_2d_array_size((void **)line_parts) == 2)
			{
				t_graph *node1 = node_exist(line_parts[0]);
				t_graph *node2 = node_exist(line_parts[1]);
				if (!node1 || !node2)
				{
					free_2dstr(line_parts);
					cut_loose();
				}
				ft_lstadd_back(&node1->links, ft_lstnew(node2));
				ft_lstadd_back(&node2->links, ft_lstnew(node1));
				free_2dstr(line_parts);
			}
			else
			{
				free_2dstr(line_parts);
				cut_loose();
			}
		}
		else
		{
			free(line);
			cut_loose();
		}
	}
}