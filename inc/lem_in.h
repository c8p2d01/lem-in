#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct gNode {
	struct gNode	**gates;
	char			*name;
}	gNode;

# include "../lft/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

gNode	*ft_gNewNode(char *data);
void	delNode(gNode *node);
void	ft_gInsert(gNode *node, size_t amount, ...);
void	ft_gClean(gNode *node);
bool	hasGate(gNode *node, gNode *next);

void	printNode(gNode *node);

#endif