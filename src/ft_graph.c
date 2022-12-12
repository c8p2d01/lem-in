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
void	ft_gInsert(gNode *node, size_t amount, ...)
{
	va_list c;
	va_start(c, amount);
	if (node->gates == NULL)
	{
		node->gates = ft_calloc((amount + 1), sizeof(gNode *));
		node->gates[amount] = NULL;
		for (size_t i = 0; i < amount; i++)
		{
			node->gates[i] = va_arg(c, gNode*);
			if (!hasGate(node->gates[i], node))
			{
				printf("connect %s to %s\n", node->name, node->gates[i]->name);
				ft_gInsert(node->gates[i], 1, node);
			}
		}
	}
	else
	{
		size_t size = arraySize((void **)node->gates);
		size_t newSize = size + amount;
		node->gates = ft_realloc(node->gates, sizeof(gNode *) * size, sizeof(gNode *) * (newSize + 1));
		while (size < newSize)
		{
			gNode *in = va_arg(c, gNode*);
			if (!in)
				break;
			printf("inserted %s\n", in->name);
			node->gates[size] = in;
			if (!hasGate(node->gates[size], node))
				ft_gInsert(node->gates[size], 1, node);
			size++;
		}
	}
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
bool	hasGate(gNode *node, gNode *next)
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

void	printNode(gNode *node)
{
	if (!node->gates[0]->name)
		printf("Error!\n");
	printf("node '%s'\n", node->name);
	for (int i = 0; node->gates && node->gates[i]; i++)
		printf("\t link to '%s'\n", node->gates[i]->name);
}

void	delNode(gNode *node)
{
	free(node->name);
	free(node->gates);
	// still need to take out the link to this nodes from the gates of its gates
}
