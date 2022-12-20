#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lft/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct gNode {
	struct gNode	**gates;
	char			*name;
	size_t			x;
	size_t			y;
}	gNode;

typedef struct globe {
	struct gNode	**allNodes;
	struct gNode	*start;
	struct gNode	*end;
	size_t			nAnts;
}	globe;

void	readData(globe *data);

gNode	*ft_gNewNode(char *data);
void	ft_gInsert(gNode *node, gNode *next);
void	ft_gClean(gNode *node);
bool	ft_hasGate(gNode *node, gNode *next);

void	printNodes(gNode **node);

size_t	arraySize(void **array);
void	freeGlobe(globe *data);

#endif
