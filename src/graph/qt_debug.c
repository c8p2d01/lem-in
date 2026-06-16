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

//int main()
//{
//	t_net	*net = catch();
//	t_graph *node1 = new_graph("1",12, 12);
//	t_graph *node2 = new_graph("2",25, 75);
//	t_graph *node3 = new_graph("3",75, 25);
//	t_graph *node4 = new_graph("4",75, 75);
//	t_graph *node5 = new_graph("5",25, 25.1);
//	t_graph *node6 = new_graph("6",55, 55);

//	t_qt_node	*root = ft_calloc(1, sizeof(t_qt_node));
//	*root = (t_qt_node){
//		.bound_x.x = 0,
//		.bound_x.y = 100,
//		.bound_y.x = 0,
//		.bound_y.y = 100,
//		.center.x = 50,
//		.center.y = 50,
//	};
//	qt_insert(root, node1);
//	qt_insert(root, node2);
//	qt_insert(root, node3);
//	qt_insert(root, node4);
//	qt_insert(root, node5);
//	qt_insert(root, node6);
//	qt_mass(root);
//	qt_print(root, 1, 42);
//}
