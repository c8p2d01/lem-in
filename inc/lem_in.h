#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lft/inc/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

# define READ_INPUT 3//STDIN_FILENO

typedef struct globe {
	struct s_room	**graph;
	struct s_room	*start;
	struct s_room	*end;
	struct s_link	**linkedlist;
	size_t			nAnts;
	size_t			maxLevel;
	struct s_path	**paths;
}	globe;

typedef struct s_path {
	struct	s_room **path;
	size_t	len;
}	t_path;

void	read_data(globe *data);

void	remove_deadend(globe *data);

void	first_level(globe *data);

bool	first_flow(t_room *node, globe *data);

void	leveling(globe *data);

bool 	after_flow(t_room *node, globe *data);

t_path	*river(t_link *flow, t_room *spring, t_room *estuary);

t_path	**cartograph(globe *data);

void	free_globe(globe *data);

void 	path_sort(globe *data);

void	mapper(t_path *river);

#endif
