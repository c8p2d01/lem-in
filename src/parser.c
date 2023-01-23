#include "../inc/lem_in.h"

/**
 * @brief Check if a line is a comment
 */
static bool	is_comment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return true;
	return false;
}

/**
 * @brief Get node index by name
 */
static ssize_t	get_node_index(globe *data, char *name)
{
	for (size_t i = 0; data->graph[i]; ++i)
	{
		if (ft_strncmp(data->graph[i]->name, name, ft_strlen(name) + 1) == 0)
			return (i);
	}
	return (-1);
}

/**
 * @brief Add a node to all nodes list
 */
static bool	add_node(globe *data, char *line)
{
	char **split = ft_split(line, ' ');
	if (ft_array_size((void **)split) != 3)
	{
		ft_putendl_fd("error: wrong node format", STDERR_FILENO);
		free_2dstr(split);
		return false;
	}

	if (split[0][0] == 'L' || split[0][0] == '#' || ft_strchr(split[0], '-') != NULL)
	{
		ft_putendl_fd("error: node name can't start with L or # or contains -", STDERR_FILENO);
		free_2dstr(split);
		return false;
	}
	t_room *node = ft_g_new_room(ft_strdup(split[0]));

	if (!ft_isnumeric(split[1]) || !ft_isnumeric(split[2]))
	{
		ft_putendl_fd("error: node position needs to be a number", STDERR_FILENO);
		free_2dstr(split);
		return false;
	}
	int x = ft_atoi(split[1]);
	int y = ft_atoi(split[2]);
	if (x < 0 || y < 0)
	{
		ft_putendl_fd("error: node position can't be negative", STDERR_FILENO);
		free_2dstr(split);
		return false;
	}
	node->x = x;
	node->y = y;

	if (data->graph == NULL)
	{
		data->graph = ft_calloc(sizeof(t_room*), 2);
		data->graph[0] = node;
	}
	else
	{
		size_t size = ft_array_size((void **)data->graph);
		data->graph = ft_realloc(data->graph, sizeof(t_room *) * (size + 1), sizeof(t_room *));
		data->graph[size] = node;
	}

	free_2dstr(split);
	return true;
}

/**
 * @brief Extract data from line to globe struct
 */
static bool	extract_data(char *line, globe *data)
{
	static bool is_gate_parsed = false;

	if (data->nAnts == 0) {
		if (!ft_isnumeric(line))
		{
			ft_putendl_fd("error: number of ants needs to be a number", STDERR_FILENO);
			return false;
		}

		int nAnts = ft_atoi(line);
		if (nAnts <= 0)
		{
			ft_putendl_fd("error: number of ants needs to be positive", STDERR_FILENO);
			return false;
		}

		data->nAnts = nAnts;
		return true;
	}

	if (!is_gate_parsed && (ft_strncmp(line, "##start", 8) == 0 || ft_strncmp(line, "##end", 6) == 0))
	{
		char *node_line;
		if (get_next_line(0, &node_line) <= 0)
		{
			ft_putendl_fd("error: get_next_line() after ##start or ##end", STDERR_FILENO);
			return false;
		}

		if (!add_node(data, node_line))
		{
			free(node_line);
			return false;
		}

		if (node_line)
			free(node_line);

		if (ft_strncmp(line, "##start", 8) == 0)
			data->start = data->graph[ft_array_size((void **)data->graph) - 1];
		else
			data->end = data->graph[ft_array_size((void **)data->graph) - 1];

		return true;
	}

	if (!is_gate_parsed && ft_strchr(line, ' ') != NULL)
		return add_node(data, line);

	if (is_gate_parsed == false)
	{
		if (data->start == NULL || data->end == NULL)
		{
			ft_putendl_fd("error: start or end not set", STDERR_FILENO);
			return 0;
		}
		is_gate_parsed = true;
	}

	char **split = ft_split(line, '-');
	if (ft_array_size((void **)split) != 2 || get_node_index(data, split[0]) == -1
		|| get_node_index(data, split[1]) == -1)
	{
		ft_putendl_fd("error: wrong link format", STDERR_FILENO);
		free_2dstr(split);
		return 0;
	}

	ssize_t node1_index = get_node_index(data, split[0]);
	ssize_t node2_index = get_node_index(data, split[1]);
	if (node1_index == -1 || node2_index == -1)
	{
		ft_putendl_fd("error: node not found for linking", STDERR_FILENO);
		free_2dstr(split);
		return 0;
	}

	if (data->linkedlist == NULL)
	{
		data->linkedlist = ft_calloc(sizeof(t_room *), 2);
		data->linkedlist[0] = ft_g_insert(data->graph[get_node_index(data, split[0])], data->graph[get_node_index(data, split[1])]);
	}
	else
	{
		size_t size = ft_array_size((void **)data->linkedlist);
		data->linkedlist = ft_realloc(data->linkedlist, sizeof(t_room *) * (size + 1), sizeof(t_room *));
		data->linkedlist[size] = ft_g_insert(data->graph[get_node_index(data, split[0])], data->graph[get_node_index(data, split[1])]);
	}

	free_2dstr(split);
	return true;
}

/**
 * @brief Read data from standard input
 */
void	read_data(globe *data)
{
	char *line = NULL;
	int read_size;

	do
	{
		read_size = get_next_line(STDIN_FILENO, &line);
		if (read_size != 1)
		{
			if (read_size == 0)
				free(line);
			break;
		}

		if (ft_strlen(line) == 0 || is_comment(line))
		{
			free(line);
			continue;
		}

		if (!extract_data(line, data))
		{
			free(line);
			free_globe(data);
			exit(EXIT_FAILURE);
		}

		free(line);
	} while (69);

	if (read_size == -1)
	{
		ft_putendl_fd("error: get_next_line()", STDERR_FILENO);
		free_globe(data);
		exit(EXIT_FAILURE);
	}

	if (data->nAnts == 0)
	{
		ft_putendl_fd("error: no ants", STDERR_FILENO);
		free_globe(data);
		exit(EXIT_FAILURE);
	}

	if (data->graph == NULL)
	{
		ft_putendl_fd("error: no nodes", STDERR_FILENO);
		free_globe(data);
		exit(EXIT_FAILURE);
	}

	if (data->start == NULL || data->end == NULL)
	{
		ft_putendl_fd("error: start or end not set", STDERR_FILENO);
		free_globe(data);
		exit(EXIT_FAILURE);
	}
}
