#include "../inc/lem_in.h"

t_path	*copy_path(t_path *river, size_t	ant)
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
	{
		// if(river->path)
		// 	free(river->path);		LEAKS?
		if (river)
			free(river);
	}
}

int		len_of_prev(t_path **paths, int i)
{
	int lens = 0;
	for (int x = 0; x < i; x ++)
		lens += paths[x]->len;
	return (lens);
}

void	ant_march(globe *data)
{
	t_list	*ants = NULL;
	t_list	*temp = ants;
	t_list	*tmp;
	size_t	marched = 0;
	int		maxflow = ft_array_size((void**)(data->paths));
	bool	last = false;

	while ((marched < data->nAnts) || ants)
	{
		temp = ants;
		while (temp)
		{
			t_path *current_ant = (t_path *)(temp->content);
			(current_ant)->path++;
			(current_ant)->len--;
			if ((current_ant)->len > 0)
				printf("L%i-%s ", (current_ant)->ant, ((current_ant)->path[0])->name);
			tmp = temp->next;
			if (*(current_ant->path) == data->end)
			{
				int annn = current_ant->ant;
				ft_lstdelone(temp, drought); // Big time memory LEAK
				if (tmp)
					ants = ft_lstfirst(tmp);
				if (ft_lstsize(ants) == 1)
				{
					if (last == true) //Janky
					{
						ants = NULL;
						break;
					}
					last = true;
				}
			}
			temp = tmp;
		}
		printf("\n");
		for (int i = 0; i < maxflow && marched < data->nAnts; )
		{
			if (i != 0 && data->paths[i]->len > (data->nAnts - marched))
				break;
			t_path	*newAnt = copy_path(data->paths[i], marched + 1); // <-> start counting at 0 '+ 1'
			ft_lstadd_back(&ants, ft_lstnew(newAnt));
			marched++;
			i++;
		}
	}
}