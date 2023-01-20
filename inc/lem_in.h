#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lft/inc/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct globe {
	struct s_room	**graph;
	struct s_room	*start;
	struct s_room	*end;
	size_t			nAnts;
}	globe;

void	read_data(globe *data);

void	level(globe *data);

void	level_sort(globe *data);

void	remove_useless(globe *data);
void	remove_deadend(globe *data);

size_t	arraySize(void **array);

void	free_globe(globe *data);

#endif
