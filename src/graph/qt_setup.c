#include "../../inc/lem_in.h"

t_qt_node	*new_qt_root(float min_x, float min_y, float max_x, float max_y)
{
	t_qt_node	*root;

	root = ft_malloc(sizeof(t_qt_node));
	root->bound_x.x = min_x;
	root->bound_x.y = max_x;
	root->bound_y.x = min_y;
	root->bound_y.y = max_y;
	root->center.x = root->bound_x.x + (root->bound_x.y - root->bound_x.x) / 2;
	root->center.y = root->bound_y.x + (root->bound_y.y - root->bound_y.x) / 2;
	root->is_leaf = false;
	root->node = NULL;
	root->total_mass = 0;
	root->min_width = ((max_x - min_x) / max_x) / 10;
	return (root);
}

//  0 | 1
//  --+--
//  2 | 3

/**
 * allocate for a new sub tree bounds determined by quartile number
 */
t_qt_node	*new_qt_node(t_qt_node *parent, int quartile)
{
	t_qt_node	*res;

	res = ft_calloc(1, sizeof(t_qt_node));
	if (quartile % 2 == 0)
	{
		res->bound_x.x = parent->bound_x.x;
		res->bound_x.y = parent->center.x;
	}
	else
	{
		res->bound_x.x = parent->center.x;
		res->bound_x.y = parent->bound_x.y;
	}
	if (quartile < 2)
	{
		res->bound_y.x = parent->center.y;
		res->bound_y.y = parent->bound_y.y;
	}
	else
	{
		res->bound_y.x = parent->bound_y.x;
		res->bound_y.y = parent->center.y;
	}
	res->center.x = res->bound_x.x + fabs(res->bound_x.y - res->bound_x.x) / 2;
	res->center.y = res->bound_y.x + fabs(res->bound_y.y - res->bound_y.x) / 2;
	res->min_width = parent->min_width;
	return (res);
}
