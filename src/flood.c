#include "../inc/lem_in.h"

t_path	*copyAnt(t_path *river, size_t	ant)
{
	t_path	*copy = malloc(1 * sizeof(t_path));
	copy->len = river->len;
	copy->path = ft_calloc(copy->len + 1, sizeof(t_room *));
	for(int i = 0; river->path[i]; i++)
	{
		copy->path[i] = river->path[i];
	}
	copy->ant = ant;
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
			t_path *current_ant = (t_path *)(curr_lst->content);
			current_ant->len--;
			next_lst = curr_lst->next;
			if (current_ant->len > 0)
				printf("L%i-%s ", (current_ant)->ant, ((current_ant)->path[0])->name);
			else
			{
				if (curr_lst == ants)
					ants = next_lst;
				ft_lstdelone(curr_lst, drought);
				deleted ++;
			}
			curr_lst = next_lst;
		}
		printf("\n");
		for (unsigned long i = 0; data->paths[i] && marched < data->nAnts; i ++)
		{
			if (i != 0 && data->paths[i]->len > data->paths[0]->len && (data->nAnts - marched ) < len_of_prev(data->paths, i))
				break;
			t_path	*ant = copyAnt(data->paths[i], marched + 1);
			ft_lstadd_back(&ants, ft_lstnew(ant));
			created++;
			marched++;
		}
	}
}