#include "../inc/lem_in.h"

t_ant	*copyAnt(int number, int path, int position)
{
	t_ant	*copy = ft_calloc(1, sizeof(t_ant));
	copy->path = path;
	copy->position = position ;
	copy->number = number;
	return (copy);
}

void	drought(void *content)
{
	// if (content)
	// 	free((t_ant*)content);
	content = NULL;
}

unsigned long	len_of_prev(t_path **paths, int i)
{
	unsigned long lens = 0;
	for (int x = 0; x < i; x ++)
		lens += (paths[i]->len - paths[x]->len);
	return (lens);
}

void	ant_march(globe *data)
{
	t_list	*ants = NULL;
	t_list	*curr_lst = ants;
	t_list	*next_lst;
	size_t	marched = 0;
	int		maxflow = ft_array_size((void**)(data->paths));

	int created = 0;
	int deleted = 0;

	while ((marched < data->nAnts) || ants)
	{
		curr_lst = ft_lstfirst(ants);
		while (curr_lst && deleted < (int)data->nAnts)
		{
			t_ant *current_ant = (t_ant *)(curr_lst->content);
			next_lst = curr_lst->next;
			if (current_ant->position != data->paths[current_ant->path]->len)
			{
				char *s = data->paths[current_ant->path]->path[current_ant->position]->name;
				printf("L%i-%s ", (current_ant)->number, s);
			}
			else
			{
				if (curr_lst == ants)
					ants = next_lst;
				ft_lstdelone(curr_lst, drought);
				deleted ++;
			}
			current_ant->position++;
			curr_lst = next_lst;
		}
		printf("\n");
		for (unsigned long i = 0; data->paths[i] && marched < data->nAnts; i ++)
		{
			if (i != 0 && data->paths[i]->len > data->paths[0]->len && (data->nAnts - marched ) < len_of_prev(data->paths, i))
				break;
			t_ant	*ant = copyAnt(marched + 1, i, 0);
			ft_lstadd_back(&ants, ft_lstnew(ant));
			created++;
			marched++;
		}
	}
}