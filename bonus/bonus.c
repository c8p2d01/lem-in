#include "../inc/lem_in.h"

void	bonus(globe *data, char **env)
{
	(void)data;
	char	*tmp = NULL;
	char	*folder = NULL;
	for (int i = 0; env[i]; i++)
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			tmp = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
			break;
		}
	}
	if (!tmp)
		exit(1);
	folder = ft_strjoin(tmp, "/bonus/Obsidian_Vault/");
	// for (int i = 0; data->graph[i]; i++)
	// {
	// 	nodefile(data->graph[i], folder, data);
	// }
	for(int i = 0; data->paths[i]; i++)
	{
		for(int p = 0; data->paths[i]->path[p]; p++)
		{
			pathnodefile(data->paths[i]->path[p], folder, data, data->paths[i]);
			pathfile(data->paths[i]->path[p], folder, i);
		}
	}
}

void	nodefile(t_room *node, char *folder, globe *data)
{
	char	*tmp = ft_strjoin(folder, node->name);
	char	*name = ft_strjoin(tmp, ".md");
	free(tmp);
	int fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (node == data->end || node == data->start)
		write(fd, "[[infinity]]\n", 13);
	for (int i = 0; node->links && node->links[i]; i++)
	{
		t_room *other = ft_otherside(node->links[i], node);
		write(fd, "[[", 2);
		write(fd, other->name, ft_strlen(other->name));
		write(fd, "]]\n", 3);
	}
	close(fd);
	free(name);
}

void	pathnodefile(t_room *node, char *folder, globe *data, t_path *path)
{
	char	*tmp = ft_strjoin(folder, node->name);
	char	*name = ft_strjoin(tmp, ".md");
	free(tmp);
	int fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (node == data->end || node == data->start)
		write(fd, "[[infinity]]\n", 13);
	for (int i = 0; node->links && node->links[i]; i++)
	{
		t_room *other = ft_otherside(node->links[i], node);
		bool	part = false;
		for(int i = 0; path->path[i]; i++)
		{
			if (other == path->path[i])
			{
				part = true;
				break;
			}
		}
		if (!part)
			continue;
		write(fd, "[[", 2);
		write(fd, other->name, ft_strlen(other->name));
		write(fd, "]]\n", 3);
	}
	close(fd);
	free(name);
}

void	pathfile(t_room *node, char *folder, int num)
{
	char	*tmp = ft_strjoin(folder, node->name);
	char	*number = num < 18 ? ft_itoa(num) : "";
	char	*name = ft_strjoin(tmp, ".md");
	char	*add = ft_strjoin("path", number);
	free(number);
	free(tmp);
	int fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	write(fd, "[[", 2);
	write(fd, add, ft_strlen(add));
	write(fd, "]]\n", 3);
	free(add);
	close(fd);
	free(name);
}
