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

# define K_THETA   0.5
# define K_REPULSE 2500.0
# define K_SPRING  10

enum INPUT
{
	COMMENT = 1,
	ROOM = 2,
	LINK = 3,
	START = 4,
	END = 5
};

typedef struct s_graph
{
	struct s_list	*links;
	char	*name;
	int		dist;
	int		ant;
	int		path;
	bool	important;
	t_vec2d	pos;
	t_vec2d	f;
	t_vec2d	v;
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
	double	ideal_node_distance;
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

typedef struct s_qt_node
{
	t_vec2d	bound_x;
	t_vec2d	bound_y;
	t_vec2d	center;
	double	total_mass;
	bool	is_leaf;
	t_graph	*node;
	struct	s_qt_node *children[4];
	double	min_width;
} t_qt_node;

// graph setup

t_net	**catch();
t_net	*ft_new_net();
t_graph	*ft_new_graph(char *name, int x, int y);
t_link	*ft_new_link(t_graph *in, t_graph *out);

// graph utils

t_link	*ft_link_graphs(t_graph *a, t_graph *b);
t_link	*ft_are_linked(t_graph *a, t_graph *b);
void	ft_unlink_graphs(t_graph *a, t_graph *b);
size_t	n_links(t_graph *a);
t_graph	*ft_linked_to(t_graph *a, t_link *link);
t_graph	*ft_node_exist(char *name);

// graph preperation

size_t	isolate_endings();
void	isolate_graph(t_graph *a);
void	identify_nets();

// parsing utils

void	input_parser(char *file);
void	input_check();
int8_t	determine_input_type(char *line);
t_graph	*create_node(char *raw_line, t_graph **node_destination);
t_link	*create_link(char *raw_line);
void	comment_parsing(char *raw_line);

// path isolation

void	reset_distances();
void	set_distances(t_graph	*start, size_t base, size_t increment);
void	append_uninitialised(t_graph *a, t_list **queue, size_t dist);

// path tracing

void	prepare_pathing();
void	path_linking(t_graph *from, t_link *link);
bool	has_flow_from(t_graph *from, t_link *link);
t_link	*closer_neighbour(t_graph *a);
void	trace_path();

int		interrupt(char *format, ...);

// graph position calculation

void	calculate_forces();
void	attraction();
void	repulsion();
void	jitter_positions();
void	qt_insert(t_qt_node *root, t_graph *node);
void	qt_mass(t_qt_node *root);
void	qt_repulsion(t_qt_node *root, t_graph *node);
void	qt_destroy(t_qt_node *root);

// graph position utils

void		velocity_reset();
t_qt_node	*new_qt_root(float min_x, float min_y, float max_x, float max_y);
t_qt_node	*new_qt_node(t_qt_node *parent, int quartile);
int			determine_quadrant(t_qt_node *root, t_graph *node);

void		force_reset();
void		apply_forces();
void		link_force(t_link *link);

int			qt_print_node(t_graph *node, size_t indent, int q_num);
int			qt_print(t_qt_node *root, size_t indent, int q_num);

// visualisation

void	plot_graph(int(f)(t_graph *));
void	visualize_net();

// visualisation options

int		color_by_path(t_graph *a);
int		color_by_distance(t_graph *a);
int		color_by_ant(t_graph *a);

// visualisation utils

t_hook	**vis();
void	determine_max_coordinates();
void	corner_important();
void	keyhook(void *param);
void	draw_square(mlx_image_t *img, size_t x, size_t y, size_t len, int color);
void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
int		create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	draw_links(t_hook *params, mlx_image_t *img);
void	draw_nodes(t_hook *params, int(f)(t_graph *), mlx_image_t *img);

void	print_net();
#endif

// 6 04e50
// 5 0a7a0
// 1 05c90
// 