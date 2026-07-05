#include "../../inc/lem_in.h"

static int	print_indent(size_t indent)
{
	int res;
	int	i = 0;

	i = 0;
	while (i < indent)
	{
		res += printf("   ");
		i++;
	}
	return (res);
}

int	qt_print_node(t_graph *node, size_t indent, int q_num)
{
	int res;

	res = 0;
	res += print_indent(indent);
	res += printf("%i\tx: %.2f\n", q_num, node->pos.x);

	res += print_indent(indent);
	res += printf("\ty: %.2f\n", node->pos.y);
	return (res);
}

int	qt_print(t_qt_node *root, size_t indent, int q_num)
{
	int res;
	int	q;

	res = 0;
	if (root->node)
		res += qt_print_node(root->node, indent, q_num);
	res += print_indent(indent);
	res += printf("mass: %.0lf\n", root->total_mass);
	q = 0;
	while (q < 4)
	{
		//printf("q%i: %p\n", q, root->children[q]);
		if (root->children[q])
			res += qt_print(root->children[q], indent + 1, q + 1);
		q++;
	}
}

void	qt_sub_plot(t_qt_node *root, mlx_image_t *img, bool nodes, bool center)
{
	t_hook	*params;
	int		q;
	t_vec2d	p1;
	t_vec2d	p2;
	int		frame_color = create_rgbt(255, 0, 255, 255);
	int		node_color = create_rgbt(0, 255, 0, 255);
	int		center_color = create_rgbt(0, 0, 255, 255);

	params = *vis();
	p1.x = root->bound_x.x;
	p1.y = root->bound_y.x;
	p2.x = root->bound_x.x;
	p2.y = root->bound_y.y;
	draw_line(img, point_on_image(p1), point_on_image(p2), frame_color);
	p2.x = root->bound_x.y;
	p2.y = root->bound_y.x;
	draw_line(img, point_on_image(p1), point_on_image(p2), frame_color);
	p1.x = root->bound_x.y;
	p1.y = root->bound_y.y;
	draw_line(img, point_on_image(p1), point_on_image(p2), frame_color);
	p2.x = root->bound_x.x;
	p2.y = root->bound_y.y;
	draw_line(img, point_on_image(p1), point_on_image(p2), frame_color);
	if (nodes && root->node)
		draw_square(img, point_on_image(root->node->pos), NODE_SIZE, node_color);
	if (center)
		draw_square(img, point_on_image(root->center), root->total_mass + NODE_SIZE / 2, center_color);
	q = 0;
	while (q < 4)
	{
		if (root->children[q])
			qt_sub_plot(root->children[q], img, nodes, center);
		q++;
	}
}

void	qt_plot(t_qt_node *root, bool nodes, bool center)
{
	t_hook		*params;
	mlx_image_t	*img;
	t_list		*new;

	params = *vis();
	img = mlx_new_image(params->mlx, WDTH, HGHT);
	if (!img)
		interrupt("images failed\n");
	qt_sub_plot(root, img, nodes, center);
	new = ft_lstnew(img);
	if (!new)
		interrupt("images failed\n");
	ft_lstadd_back(&params->images, new);
	params->n_images++;
}

//int main()
//{
//	t_net	*net = *catch();
//	t_hook	*params = *vis();

//	t_qt_node	*root = ft_calloc(1, sizeof(t_qt_node));
//	*root = (t_qt_node){
//		.bound_x.x = 0,
//		.bound_x.y = 100,
//		.bound_y.x = 0,
//		.bound_y.y = 100,
//		.center.x = 50,
//		.center.y = 50,
//	};
//	qt_mass(root);
//	qt_print(root, 1, 42);
//}
