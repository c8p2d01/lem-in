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
		if(river->path)
			free(river->path);
		if (river)
			free(river);
	}
}

void	ant_march(globe *data)
{
	t_list	*ants = NULL;
	t_list	*temp = ants;
	t_list	*tmp;
	size_t	marched = 0;
	int		maxflow = ft_array_size((void**)(data->paths));

	while (marched < data->nAnts || ants)
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
			if ((current_ant)->path[0] == data->end)
			{
				ft_lstdelone(temp, NULL /* drought */); // Big time memory LEAK
				ants = ft_lstfirst(tmp);
			}
			temp = tmp;
		}
		printf("\n");
		for (int i = 0; i < maxflow && marched < data->nAnts; )
		{
			t_path	*newAnt = copy_path(data->paths[i], marched + 1); // <-> start counting at 0 '+ 1'
			ft_lstadd_back(&ants, ft_lstnew(newAnt));
			marched++;
			i++;
		}
	}
}