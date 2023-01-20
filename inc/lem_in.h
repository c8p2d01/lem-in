#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lft/inc/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <stdint.h>

# include <assert.h> // TODO: remove

typedef struct globe {
	struct t_graph	**allNodes;
	struct t_graph	*start;
	struct t_graph	*end;
	size_t			nAnts;
	size_t			nPaths;
}	globe;

void	readData(globe *data);

void	add_level(globe *data);
void	delete_useless_node(globe *data);
void	delete_deadend(globe *data);
void	add_directional(globe *data);
void	unlink_same_level(globe *data);
void	sort_level(globe *data);
void	remove_input_links(globe *data);
void	remove_output_links(globe *data);
void	find_all_shortest_paths(globe *data);
void	print_paths(globe *data);

size_t	arraySize(void **array);

void	free_globe(globe *data);

#endif
