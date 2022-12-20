#include "../inc/lem_in.h"

/**
 * @brief Free globe struct
 */
void	freeGlobe(globe *data)
{
	for (size_t i = 0; data->allNodes[i] != NULL; ++i)
	{
		free(data->allNodes[i]->name);
		free(data->allNodes[i]->gates);
		free(data->allNodes[i]);
	}
	free(data->allNodes);
}

/**
 * @brief Allocate a new node
 */
gNode	*ft_gNewNode(char *data)
{
	gNode *res = ft_calloc(sizeof(gNode), 1);
	res->name = data;
	return (res);
}

/**
 * @brief Insert one node to another
 */
void	ft_gInsert(gNode *node, gNode *next)
{
	if (node->gates == NULL)
	{
		node->gates = ft_calloc(2, sizeof(gNode *));
		node->gates[0] = next;
		if (!ft_hasGate(node->gates[0], node))
			ft_gInsert(node->gates[0], node);
	}
	else
	{
		size_t size = arraySize((void **)node->gates);
		size_t newSize = size + 1;
		node->gates = ft_realloc(node->gates, sizeof(gNode *) * size, sizeof(gNode *) * (newSize + 1));
		gNode *in = next;
		node->gates[size] = in;
		if (!ft_hasGate(node->gates[size], node))
			ft_gInsert(node->gates[size], node);
	}
}

/**
 * @brief free a node and remove its traces from tho nodes it was connected to
 */
void	ft_gErase(gNode *node)
{
	size_t i = 0;
	while (node->gates && node->gates[i])
	{
		size_t	s = arraySize((void **)node->gates[i]->gates);
		gNode	**new = ft_calloc(s, sizeof(gNode*));
		size_t	n = 0;
		size_t	o = 0;
		while (n < s)
		{
			if (node->gates[i]->gates[n + o] == node)
				o++;
			new[n] = node->gates[i]->gates[n + o];
			n++;
		}
		i++;
	}
	free(node->gates);
	free(node->name);
	free(node);
}

void	ft_gClean(gNode *node)
{
	size_t amount = 0;
	while (node->gates[amount] != NULL)
		amount++;
	gNode **comp = ft_calloc((amount + 1), sizeof(gNode*));
	for (size_t i = 0; i < amount; i++)
	{
		int a = 0;
		while (comp[a] != NULL && comp[a] != node->gates[i])
			a++;
		if (comp[a])
			continue;
		while (comp[a] != NULL)
			a++;
		comp[a] = node->gates[i];
	}
}

/**
 * @brief Check if a node is already connected to another node
 */
bool	ft_hasGate(gNode *node, gNode *next)
{
	if (node == NULL || node->gates == NULL)
		return (false);
	for (int i = 0; node->gates && node->gates[i]; i++)
	{
		if (next == node->gates[i])
			return(true);
	}
	return (false);
}

/**
 * @brief Print all nodes and its gates
 * @note Debug
 */
void	printNodes(gNode **node)
{
	for (size_t i = 0; node[i]; ++i)
	{
		printf("node '%s'\n", node[i]->name);
		for (size_t j = 0; node[i]->gates && node[i]->gates[j]; ++j)
		{
			printf("\t link to '%s'\n", node[i]->gates[j]->name);
		}
	}
}
