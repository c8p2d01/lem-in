#include "../../inc/lem_in.h"

//  0 | 1
//  --+--
//  2 | 3

int		determine_quadrant(t_qt_node *root, t_graph *node)
{
	int	quadrant;

	if (node->pos.y > root->center.y)
	{
		if (node->pos.x < root->center.x)
			quadrant = 0;
		else
			quadrant = 1;
	}
	else
	{
		if (node->pos.x < root->center.x)
			quadrant = 2;
		else
			quadrant = 3;
	}
	if (!root->children[quadrant])
		root->children[quadrant] = new_qt_node(root, quadrant);
	return (quadrant);
}

void	qt_insert(t_qt_node *root, t_graph *node)
{
	int	child_quadrant;

	if (!root->node)
	{
		root->node = node;
		root->is_leaf = true;
	}
	else
	{
		child_quadrant = determine_quadrant(root, node);
		qt_insert(root->children[child_quadrant], node);
		if (root->is_leaf == true)
		{
			child_quadrant = determine_quadrant(root, root->node);
			if (equal2d(&root->node->pos, &node->pos, root->min_width))
			{
				child_quadrant = (child_quadrant + 1) % 4;
				if (!root->children[child_quadrant])
					root->children[child_quadrant] = new_qt_node(root, child_quadrant);
				root->node->pos = root->children[child_quadrant]->center;
			}
			qt_insert(root->children[child_quadrant], root->node);
			root->is_leaf = false;
		}
	}
}

/**
 * calculates recursively the total mass of a tree
 * also sets the center of the tree to its mass center
 */
void	qt_mass(t_qt_node *root)
{
	t_vec2d	mass_center;
	double	sum_x;
	double	sum_y;
	double	child_mass;
	int		q;

	sum_x = root->center.x;
	sum_y = root->center.y;
	if (root->is_leaf == true)
	{
		root->total_mass = 1;
		root->center.x = root->node->pos.x;
		root->center.y = root->node->pos.y;
	}
	else
	{
		root->center.x = 0;
		root->center.y = 0;
		q = 0;
		while (q < 4)
		{
			if (root->children[q])
			{
				qt_mass(root->children[q]);
				root->center.x += root->children[q]->total_mass * root->children[q]->center.x;
				root->center.y += root->children[q]->total_mass * root->children[q]->center.y;
				root->total_mass += root->children[q]->total_mass;
			}
			q++;
		}
		root->center.x /= root->total_mass;
		root->center.y /= root->total_mass;
	}
}

void	qt_repulsion(t_qt_node *root, t_graph *node)
{
	t_vec2d	connection;
	double	distance;
	double	width;
	double	force;
	int		q;

	if (!root || !node || root->total_mass == 0.0 || root->node == node)
		return;
	connection = connect2d(root->center, node->pos);
	distance = veclen2d(&connection);
	if (distance == 0.0)
		return;

	width = root->bound_x.y - root->bound_x.x;
	if (root->is_leaf || (distance / width) > K_THETA)
	{
		force = (K_REPULSE * root->total_mass) / (distance * distance);
		node->f.x -= force * (connection.x / distance);
		node->f.y -= force * (connection.y / distance);
	}
	else
	{
		q = 0;
		while (q < 4)
		{
			if (root->children[q])
				qt_repulsion(root->children[q], node);
			q++;
		}
	}
}

void	qt_destroy(t_qt_node *root)
{
	int		q;

	q = 0;
	while (q < 4)
	{
		if (root->children[q])
		{
			qt_destroy(root->children[q]);
		}
		q++;
	}
	ft_store_mem(root, sizeof(t_qt_node));
}
