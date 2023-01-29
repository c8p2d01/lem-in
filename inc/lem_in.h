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
	struct s_link	**linkedlist;
	size_t			nAnts;
	size_t			maxLevel;
	struct s_path	*paths;
}	globe;

typedef struct s_path {
	struct	s_room **path;
	size_t	len;
}	t_path;

bool	flow(t_room *node, globe *data);

void	read_data(globe *data);

void	first_level(globe *data);

void	leveling(globe *data);

void	remove_deadend(globe *data);

void	free_globe(globe *data);

#endif
