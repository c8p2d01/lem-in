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
	bool	pathed;
	t_list	*paths;
	int		packets;
}	t_net;

typedef struct s_content
{
	char	*name;
	int		level;
	int		x;
	int		y;
	int		ant;
	int		path;
}	t_content;

typedef struct s_info
{
	bool	active;
	int		flow;
}	t_info;

t_net	**catch();

t_graph	*node_exist(char	*name);
bool	counter_flow(t_graph *node, t_link *link);
void	set_flow(t_graph *node, t_link *link);

void	print_net();
void	print_node(void *iter);
void	print_node_and_links(void *iter);
void	print_path(void *iter);
void	print_paths();

void	input_parser(char *file);

void	tectonics();
void	flatten();
void	flow();
void	drain();

void	path_step(t_list *path);
void	path_step_print(t_list *path);
void	send_off();

void	cut_loose();
void	prune_orphans();
void	deactivate_ends();
void	prune_subnets();

void	bonus();
void	assignColorToPath(char **env);

#endif

// 6 04e50
// 5 0a7a0
// 1 05c90
// 