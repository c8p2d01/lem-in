#ifndef LEM_IN_H
# define LEM_IN_H

# include "../ft_libft/inc/libft.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

# ifndef READ_INPUT
#  define READ_INPUT STDIN_FILENO
# endif

# define FAILSAFE atexit

typedef struct s_net
{
	t_list	*graph_nodes;
	t_list	*graph_links;
	t_graph	*start;
	t_graph	*end;
	int		packets;
}	t_net;

typedef struct s_content
{
	char	*name;
	int		level;
	int		x;
	int		y;
}	t_content;

typedef struct s_info
{
	bool	active;
	int		flow;
}	t_info;

t_net	**catch();

t_graph	*node_exist(char	*name);
void	print_net();

void	input_parser(char *file);

void	tectonics();

void	cut_loose();
void	prune_orphans();
void	deactivate_ends();
void	prune_subnets();

#endif
