#include "../inc/lem_in.h"

t_path	*copy_path(t_path *river, size_t	ant)
{
	t_path	*copy = ft_calloc(1, sizeof(t_path));
	copy->len = river->len;
	copy->path = ft_calloc(copy->len + 2, sizeof(t_room *));
	for(int i = 0; i < copy->len; i++)
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
	{
		// if(river->path)
		// 	free(river->path);		LEAKS?
		if (river)
			free(river);
	}
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

	while ((marched < data->nAnts) || ants)
	{
		curr_lst = ants;
		while (curr_lst)
		{
			t_path *current_ant = (t_path *)(curr_lst->content);
			current_ant->path++;
			current_ant->len--;
			if (current_ant->len > 0)
				printf("L%i-%s ", current_ant->ant, (current_ant->path[0])->name);
			next_lst = curr_lst->next;
			if ((current_ant->path[0]) == data->end)
			{
				if (curr_lst == ants)
					ants = next_lst;
				ft_lstdelone(curr_lst, drought);
			}
			curr_lst = next_lst;
		}
		printf("\n");
		for (unsigned long i = 0; data->paths[i] && marched < data->nAnts; i ++)
		{
			if (i != 0 && data->paths[i]->len > data->paths[0]->len && (data->nAnts - marched ) < len_of_prev(data->paths, i))
				break;
			t_path	*newAnt = copy_path(data->paths[i], marched + 1); // <-> start counting at 0 '+ 1'
			ft_lstadd_back(&ants, ft_lstnew(newAnt));
			marched++;
		}
	}
}