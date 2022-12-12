#include "../inc/lem_in.h"

// allocate space foe a new node
gNode	*ft_gNewNode(char *data)
{
	gNode *res = malloc(sizeof(gNode));
	res->name = data;
	res->gates = NULL;
	return (res);
}

// connect a node to an amount of other nodes
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
		struct timeval	time;
		gettimeofday(&time, NULL);
		printf("\e[38;5;%im", time.tv_usec % 228);
		printf("before\n");
		printNode(node);

		int i = 0;
		int j = 0;
		size_t l = 0;
		while (node->gates[i] != NULL)
			i++;
		gNode **new = ft_calloc((i + amount + 1), sizeof(gNode *));
		new[i + amount] = NULL;
		while (node->gates[j] != NULL)
		{
			new[j] = node->gates[j];
			j++;
		}
		free(node->gates);
		node->gates = new;
		while (l < amount)
		{
			gNode	*in = va_arg(c, gNode*);
			if (!in)
				break;
			printf("inserted %s\n", in->name);
			new[j + l] = in;
			if (!hasGate(new[j + l], node))
				ft_gInsert(new[j + l], 1, node);
			l++;
		}
		free(node->gates);
		node->gates = new;

		printf("\e[38;5;%im", time.tv_usec % 228);
		printf("after\n");
		printNode(node);
		printf("\e[0m");
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
