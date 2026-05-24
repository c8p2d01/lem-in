#ifndef LEM_IN_H
# define LEM_IN_H

# include "../ft_libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/time.h>

# ifndef READ_INPUT
#  define READ_INPUT STDIN_FILENO
# endif

typedef struct s_graph
{
	struct s_list	*links;
	char	*name;
	int		dist;
	int		x;
	int		y;
	int		ant;
	int		path;
	bool	important;
}	t_graph;

typedef struct s_link
{
	struct s_graph	*from;
	struct s_graph	*to;
	bool	active;
	int		flow;
}	t_link;

typedef struct s_path
{
	t_list	*path_nodes;
}	t_path;

typedef struct s_net
{
	t_list	*graph_nodes;
	t_list	*graph_links;
	t_graph	*start;
	t_graph	*end;
	size_t	n_paths;
	t_path	*paths;
	int		packets;

	int		max_x;
	int		min_x;
	int		max_y;
	int		min_y;
}	t_net;



t_net	**catch();

t_net	*ft_new_net();

t_graph	*ft_new_graph(char *name, int x, int y);

t_link	*ft_new_link(t_graph *in, t_graph *out);

t_link	*ft_are_linked(t_graph *a, t_graph *b);

t_link	*ft_link_graphs(t_graph *a, t_graph *b);

void	ft_unlink_graphs(t_graph *a, t_graph *b);

t_graph	*ft_linked_to(t_graph *a, t_link *link);

t_graph	*ft_node_exist(char *name);

bool	counter_flow(t_graph *node, t_link *link);
void	set_flow(t_graph *node, t_link *link);

void	square(mlx_image_t *img, size_t x, size_t y, size_t len, int color);
void	determine_max_coordinates();
int		create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	visualize_net();

void	input_parser(char *file);

size_t	n_links(t_graph *a);
void	isolate_graph(t_graph *a);
size_t	isolate_endings();

void	append_uninitialised(t_graph *a, t_list **queue, size_t dist);
void	set_distances();
void	reset_distances();
t_graph	*closer_neighbour(t_graph *a);
void	path_linking(t_graph *a, t_graph *b);
void	set_path(t_list *path_nodes);
void	trace_path();

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

int		interrupt(char *format, ...);

#endif

// 6 04e50
// 5 0a7a0
// 1 05c90
// 