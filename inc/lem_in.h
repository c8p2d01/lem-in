#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lft/inc/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct globe {
	struct t_graph	**allNodes;
	struct t_graph	*start;
	struct t_graph	*end;
	size_t			nAnts;
}	globe;

void	readData(globe *data);

void	unlink_equals(t_graph *node);
void	dead_ends(t_graph *node, globe *data);

void 	sort_links(t_graph *node);
void	level(globe *data);
void	level_sort(globe *data);

size_t	arraySize(void **array);

void	freeGlobe(globe *data);

#endif
