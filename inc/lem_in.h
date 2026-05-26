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
	float	x;
	float	y;
	int		ant;
	int		path;
	bool	important;
	t_vec2d	fpos;
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
	t_list	*path_links;
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

	bool	visualize;
	bool	simulate;
}	t_net;

typedef struct s_hook
{
	mlx_t	*mlx;
	t_list	*images;
	size_t	n_images;
	float	max_x;
	float	min_x;
	float	max_y;
	float	min_y;
	bool	press;
}	t_hook;

enum INPUT {
	COMMENT = 1,
	ROOM = 2,
	LINK = 3,
	START = 4,
	END = 5
};

t_net	**catch();
t_net	*ft_new_net();
t_graph	*ft_new_graph(char *name, int x, int y);
t_link	*ft_new_link(t_graph *in, t_graph *out);

t_link	*ft_are_linked(t_graph *a, t_graph *b);
t_link	*ft_link_graphs(t_graph *a, t_graph *b);
void	ft_unlink_graphs(t_graph *a, t_graph *b);
t_graph	*ft_linked_to(t_graph *a, t_link *link);
t_graph	*ft_node_exist(char *name);

void	square(mlx_image_t *img, size_t x, size_t y, size_t len, int color);
void	determine_max_coordinates();
int		create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	visualize_net();

int8_t	determine_input_type(char *line);
t_graph	*create_node(char *raw_line, t_graph **node_destination);
t_link	*create_link(char *raw_line);
void	comment_parsing(char *raw_line);
void	input_check();
void	input_parser(char *file);

size_t	n_links(t_graph *a);
void	isolate_graph(t_graph *a);
size_t	isolate_endings();

void	append_uninitialised(t_graph *a, t_list **queue, size_t dist);
void	set_distances(t_graph	*start, size_t base, size_t increment);
void	reset_distances();
void	identify_nets();
void	prepare_pathing();
void	path_linking(t_graph *from, t_link *link);
bool	has_flow_from(t_graph *from, t_link *link);
t_link	*closer_neighbour(t_graph *a);
void	trace_path();

void	cut_loose();
void	prune_orphans();
void	deactivate_ends();
void	prune_subnets();

int		interrupt(char *format, ...);

void	antigravity(t_graph *a);
void	link_force(t_graph *a);
void	calculate_forces();
size_t	apply_forces();

t_hook	**vis();
void	keyhook(void *param);
void	square(mlx_image_t *img, size_t x, size_t y, size_t len, int color);
void	line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
void	determine_max_coordinates();
int		create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	draw_links(t_hook *params, mlx_image_t *img);
int	color_by_path(t_graph *a);
int		color_by_distance(t_graph *a);
int		color_by_ant(t_graph *a);
void	draw_nodes(t_hook *params, int(f)(t_graph *), mlx_image_t *img);
void	plot_graph(int(f)(t_graph *));
void	visualize_net();

#endif

// 6 04e50
// 5 0a7a0
// 1 05c90
// 