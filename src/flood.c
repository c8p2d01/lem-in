#include "../inc/lem_in.h"

t_path	*newAnt(ssize_t path, ssize_t len, ssize_t	ant)
{
	t_path	*copy = ft_calloc(1, sizeof(t_path));
	copy->path = NULL;
	copy->pathNumber = path;
	copy->position = 0;
	copy->len = len;
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
			printf("READ ANT %zi pId %zi POS %zi pLen %zi\n", current_ant->ant, current_ant->pathNumber, current_ant->position, current_ant->len);
			current_ant->len--;
			// current_ant->position++;
			// next_lst = curr_lst->next;
			// if (current_ant->len > 0)
			// 	printf("L%zi-%s ", current_ant->ant, data->paths[current_ant->pathNumber]->path[current_ant->position]->name);
			// else
			// {
			// 	if (curr_lst == ants)
			// 		ants = next_lst;
			// 	ft_lstdelone(curr_lst, drought);
			// 	deleted ++;
			// }
			// curr_lst = next_lst;
		}
		printf("\n");
		for (unsigned long i = 0; data->paths[i] && marched < data->nAnts; i ++)
		{
			if (i != 0 && data->paths[i]->len > data->paths[0]->len && (data->nAnts - marched ) < len_of_prev(data->paths, i))
				break;
			t_path	*ant = newAnt(i, data->paths[i]->len, marched + 1);
			printf("NEW ANT %zi pId %zi POS %zi pLen %zi\n", ant->ant, ant->pathNumber, ant->position, ant->len);
			ft_lstadd_back(&ants, ft_lstnew(newAnt));
			created++;
			marched++;
		}
	}
}