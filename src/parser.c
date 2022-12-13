#include "../inc/lem_in.h"

/**
 * @brief Get 2D array size
 */
size_t	arraySize(void **array)
{
	size_t i = 0;
	while (array[i])
		i++;
	return i;
}

/**
 * @brief Check if a line is a comment
 */
static bool	isComment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return true;
	return false;
}

/**
 * @brief Get node index by name
 */
static ssize_t	getNodeIndex(globe *data, char *name)
{
	size_t i = 0;
	while (data->allNodes[i])
	{
		if (ft_strncmp(data->allNodes[i]->name, name, ft_strlen(name) + 1) == 0)
			return i;
		i++;
	}
	return -1;
}

/**
 * @brief Add a node to all nodes list
 */
static bool	addNode(globe *data, char *line)
{
	char **split = ft_split(line, ' ');
	if (arraySize((void **)split) != 3)
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
	gNode *node = ft_gNewNode(ft_strdup(split[0]));

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

	if (data->allNodes == NULL)
	{
		data->allNodes = ft_calloc(sizeof(gNode *), 2);
		data->allNodes[0] = node;
	}
	else
	{
		size_t size = arraySize((void **)data->allNodes);
		data->allNodes = ft_realloc(data->allNodes, sizeof(gNode *) * size, sizeof(gNode *) * (size + 2));
		data->allNodes[size] = node;
	}

	free_2dstr(split);
	return true;
}

/**
 * @brief Extract data from line to globe struct
 */
static bool	extractData(char *line, globe *data)
{
	static bool isGateParse = false;

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

	if (!isGateParse && (ft_strncmp(line, "##start", 8) == 0 || ft_strncmp(line, "##end", 6) == 0))
	{
		char *nodeLine;
		if (get_next_line(0, &nodeLine) <= 0)
		{
			ft_putendl_fd("error: get_next_line() after ##start or ##end", STDERR_FILENO);
			return false;
		}

		if (!addNode(data, nodeLine))
		{
			free(nodeLine);
			return false;
		}

		if (ft_strncmp(line, "##start", 8) == 0)
			data->start = data->allNodes[arraySize((void **)data->allNodes) - 1];
		else
			data->end = data->allNodes[arraySize((void **)data->allNodes) - 1];

		return true;
	}

	if (!isGateParse && ft_strchr(line, ' ') != NULL)
		return addNode(data, line);

	if (isGateParse == false)
	{
		if (data->start == NULL || data->end == NULL)
		{
			ft_putendl_fd("error: start or end not set", STDERR_FILENO);
			return 0;
		}
		isGateParse = true;
	}

	char **split = ft_split(line, '-');
	if (arraySize((void **)split) != 2)
	{
		ft_putendl_fd("error: wrong link format", STDERR_FILENO);
		free_2dstr(split);
		return 0;
	}
	ssize_t node1Index = getNodeIndex(data, split[0]);
	ssize_t node2Index = getNodeIndex(data, split[1]);
	if (node1Index == -1 || node2Index == -1)
	{
		ft_putendl_fd("error: node not found for linking", STDERR_FILENO);
		free_2dstr(split);
		return 0;
	}
	ft_gInsert(data->allNodes[node1Index], 1, data->allNodes[node2Index]);

	free_2dstr(split);
	return true;
}

/**
 * @brief Read data from standard input
 */
void	readData(globe *data)
{
	char *line = NULL;
	ssize_t readRet;

	do
	{
		readRet = get_next_line(STDIN_FILENO, &line);
		if (readRet != 1)
		{
			if (readRet == 0)
				free(line);
			break;
		}

		if (ft_strlen(line) == 0 || isComment(line))
		{
			free(line);
			continue;
		}

		if (!extractData(line, data))
		{
			free(line);
			freeGlobe(data);
			exit(EXIT_FAILURE);
		}

		free(line);
	} while (69);

	if (readRet == -1)
	{
		ft_putendl_fd("error: get_next_line()", STDERR_FILENO);
		freeGlobe(data);
		exit(EXIT_FAILURE);
	}

	if (data->nAnts == 0)
	{
		ft_putendl_fd("error: no ants", STDERR_FILENO);
		freeGlobe(data);
		exit(EXIT_FAILURE);
	}

	if (data->allNodes == NULL)
	{
		ft_putendl_fd("error: no nodes", STDERR_FILENO);
		freeGlobe(data);
		exit(EXIT_FAILURE);
	}

	if (data->start == NULL || data->end == NULL)
	{
		ft_putendl_fd("error: start or end not set", STDERR_FILENO);
		freeGlobe(data);
		exit(EXIT_FAILURE);
	}
}
