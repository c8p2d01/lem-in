#include "../inc/lem_in.h"

enum INPUT {
	ROOM = 1,
	START = 2,
	END = 3,
	LINK = 4
};

void	input_parser(char *file)
{
	int16_t		fd;
	char		*line;
	char		*trim;
	int8_t		input_type;
	char		**line_parts;
	t_net		*net;
	t_list		*lst;
	t_graph		*node;
	t_graph		*linked_node;
	t_link		*link;
	t_content	*c;
	t_info		*i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("invalid File\n");
		exit(-1);
	}

	net = *catch();
	input_type = ROOM;
	line = get_next_line(fd);
	while (line)
	{
		trim = ft_strtrim(line, " \n");
		free(line);
		line = trim;
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
			net->packets = ft_atoi(line);
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (line[0] && line[0] == '#')
		{
			if (line[1] && line[1] == '#')
			{
				if (!ft_strncmp(line, "##start", 8))
				{
					printf("%s\n", line);
					if (input_type == LINK)
						break;
					input_type = START;
				}
				if (!ft_strncmp(line, "##end", 6))
				{
					printf("%s\n", line);
					if (input_type == LINK)
						break;
					input_type = END;
				}
			}
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (input_type != LINK && ft_strchr(line, '-'))
			input_type = LINK;
		if (input_type != LINK)
		{
			line_parts = ft_split(line, ' ');
			if (ft_2d_array_size((void **)line_parts) == 3)
			{
				c = malloc(1 * sizeof(t_content));
				*c = (t_content){
					.name = ft_strdup(line_parts[0]),
					.level = 0,
					.x = ft_atoi(line_parts[1]),
					.y = ft_atoi(line_parts[2]),
					.ant = -1
				};
				node = ft_new_graph(c);
				lst = ft_lstnew((void *)node);
				ft_lstadd_back(&(net->graph_nodes), lst);
				free_2dstr(line_parts);
			}
			else
			{
				free_2dstr(line_parts);
				cut_loose();
			}
			if (input_type == START)
			{
				net->start = node;
				input_type = ROOM;
			}
			if (input_type == END)
			{
				net->end = node;
				input_type = ROOM;
			}
		}
		else
		{
			line_parts = ft_split(line, '-');
			if (ft_2d_array_size((void **)line_parts) == 2)
			{
				node = node_exist(line_parts[0]);
				linked_node = node_exist(line_parts[1]);
				i = malloc(sizeof(t_info));
				*i = (t_info){
					.active = true,
					.flow = 0
				};
				if (node && linked_node && !ft_has_link(node, linked_node))
				{
					link = ft_new_link(node, linked_node, i);
					ft_lstadd_back(&(net->graph_links), ft_lstnew(link));
					ft_lstadd_back(&(node->links), ft_lstnew(link));
					ft_lstadd_back(&(linked_node->links), ft_lstnew(link));
				}
			}
			free_2dstr(line_parts);
		}
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		free(line);
		cut_loose();
	}
}