#include "../inc/lem_in.h"

t_ant	*copyAnt(int path, int position, int number)
{
	t_ant	*copy = malloc(1 * sizeof(t_ant));
	copy->path = path;
	copy->position = position;
	copy->position = number;
	return (copy);
}

void	drought(void *content)
{
	t_path *river = (t_path *)content;
	if (river)
		unreach(river);
	river = NULL;
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
		while (curr_lst)
		{
			t_ant *current_ant = (t_ant *)(curr_lst->content);
			current_ant->position++;
			next_lst = curr_lst->next;
			if (current_ant->position != data->paths[current_ant->path]->len)
				printf("L%i-%s ", (current_ant)->number, (data->paths[current_ant->path])->path[current_ant->position]->name);
			else
			{
				if (curr_lst == ants)
					ants = next_lst;
				ft_lstdelone(curr_lst, drought);
				deleted ++;
			}
			curr_lst = next_lst;
		}
		printf("-c-%i--%i-d-\n", created, deleted);
		for (unsigned long i = 0; data->paths[i] && marched < data->nAnts; i ++)
		{
			if (i != 0 && data->paths[i]->len > data->paths[0]->len && (data->nAnts - marched ) < len_of_prev(data->paths, i))
				break;
			t_ant	*ant = copyAnt(i, 0, marched + 1);
			ft_lstadd_back(&ants, ft_lstnew(ant));
			created++;
			marched++;
		}
	}
}