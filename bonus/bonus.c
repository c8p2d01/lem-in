#include "../inc/lem_in.h"
#include "bonus.h"

char	*G_Group_Identifier[47] = {
	"11111111",
	"22222222",
	"33333333",
	"44444444",
	"55555555",
	"66666666",
	"77777777",
	"88888888",
	"99999999",
	"00000000",
	"aaaaaaaa",
	"bbbbbbbb",
	"cccccccc",
	"dddddddd",
	"eeeeeeee",
	"ffffffff",
	"gggggggg",
	"hhhhhhhh",
	"iiiiiiii",
	"jjjjjjjj",
	"kkkkkkkk",
	"llllllll",
	"mmmmmmmm",
	"nnnnnnnn",
	"oooooooo",
	"pppppppp",
	"qqqqqqqq",
	"rrrrrrrr",
	"ssssssss",
	"tttttttt",
	"uuuuuuuu",
	"vvvvvvvv",
	"wwwwwwww",
	"xxxxxxxx",
	"yyyyyyyy",
	"zzzzzzzz",
	"AAAAAAAA",
	"BBBBBBBB",
	"CCCCCCCC",
	"DDDDDDDD",
	"EEEEEEEE",
	"FFFFFFFF",
	"GGGGGGGG",
	"HHHHHHHH",
	"IIIIIIII",
	"JJJJJJJJ",
	"KKKKKKKK"
};

void	assignColorToPath(char **env)
{
	t_net	*net;

	net = *catch();
	char	*pwd = NULL;
	for (int i = 0; env[i]; i++)
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
			break;
		}
	}

	char	*folder = ft_strjoin(pwd, "/bonus/Obsidian_Vault/.obsidian/graph.json");

	int fd = open(folder, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	t_color a;
	a.r = 255;
	a.g = 255;
	a.b = 255;
	t_color b;
	b.r = 0;
	b.g = 0;
	b.b = 0;
	char	*tmp = ft_itoa(create_gradient_color(1, a, b));
	ft_printf_fd(fd, "%s%s%s%s%s%s%s%s%s",
				"{\n",
				"  \"collapse-filter\": false,\n",
				"  \"search\": \"\",\n",
				"  \"showTags\": false,\n",
				"  \"showAttachments\": false,\n",
				"  \"hideUnresolved\": true,\n",
				"  \"showOrphans\": true,\n",
				"  \"collapse-color-groups\": true,\n",
				"  \"colorGroups\": [\n");
	ft_printf_fd(fd, "%s%s%s%s%s%s%s%s",
				"    {\n",
				"      \"query\": \"infinity\",\n",
				"      \"color\": {\n",
				"        \"a\": 1,\n",
				"        \"rgb\": ",
				tmp,
				"}\n",
				"    },\n");
	if (tmp)
		free(tmp);

	int		nPath = ft_lstsize(net->paths);
	for (int i = 0; i < nPath; i++)
	{
		// char	*pathnumber;
		char	*tmp = ft_itoa(create_multi_gradient(((float)i / (float)nPath), 7, 255,0,0, 255,0,255, 0,0,255, 0,255,255, 0,255,0, 255,255,0, 255,0,0));
		ft_printf_fd(fd, "%s%s%s%s%s%s%s%s%s%s%s%s", 
				"    {\n",
				"      \"query\": \"",
				G_Group_Identifier[i],
				"\",\n",
				"      \"color\": {\n",
				"        \"a\": 1,\n",
				"        \"rgb\": ",
				(tmp && tmp[0] == '0' ? "1": ""),
				tmp,
				"}\n",
				"    }",
				i + 1 < nPath ? ",\n" : "\n");
		// if (pathnumber)
			// free(pathnumber);
		if (tmp)
			free(tmp);
	}
	
	ft_printf_fd(fd, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
				"  ],\n",
				"  \"collapse-display\": false,\n",
				"  \"showArrow\": false,\n",
				"  \"textFadeMultiplier\": 3,\n",
				"  \"nodeSizeMultiplier\": 5,\n",
				"  \"lineSizeMultiplier\": 5,\n",
				"  \"collapse-forces\": false,\n",
				"  \"centerStrength\": 0.1,\n",
				"  \"repelStrength\": 20,\n",
				"  \"linkStrength\": 1,\n",
				"  \"linkDistance\": 58,\n",
				"  \"scale\": 0.6,\n",
				"  \"close\": false\n",
				"}\n"
				);

	close (fd);
}

//void	bonus(char **env)
//{
//	t_net	*net;

//	net = *catch();
//	assignColorToPath(env);
//	char	*tmp = NULL;
//	char	*folder = NULL;
//	for (int i = 0; env[i]; i++)
//	{
//		if (!ft_strncmp(env[i], "PWD=", 4))
//		{
//			tmp = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
//			break;
//		}
//	}
//	if (!tmp)
//		exit(1);
//	folder = ft_strjoin(tmp, "/bonus/Obsidian_Vault/");
//	t_list	*path;
//	t_list	*path2;
//	path = net->paths;
//	for(int i = 0; path; path = path->next)
//	{
//		path2 = path;
//		for(int p = 0; data->paths[i]->path[p]; p++)
//		{
//			pathnodefile(data->paths[i]->path[p], folder, data, data->paths[i]);
//			pathfile(data->paths[i]->path[p], folder, i);
//		}
//	}
//}

//void	pathnodefile(t_room *node, char *folder, globe *data, t_path *path)
//{
//	char	*tmp = ft_strjoin(folder, node->name);
//	char	*name = ft_strjoin(tmp, ".md");
//	free(tmp);
//	int fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
//	if (node == data->end || node == data->start)
//		write(fd, "[[infinity]]\n", 13);
//	for (int i = 0; node->links && node->links[i]; i++)
//	{
//		t_room *other = ft_otherside(node->links[i], node);
//		bool	part = false;
//		for(int i = 0; path->path[i]; i++)
//		{
//			if (other == path->path[i])
//			{
//				part = true;
//				break;
//			}
//		}
//		if (!part)
//			continue;
//		write(fd, "[[", 2);
//		write(fd, other->name, ft_strlen(other->name));
//		write(fd, "]]\n", 3);
//	}
//	close(fd);
//	free(name);
//}

//void	pathfile(t_room *node, char *folder, int num)
//{
//	char	*tmp = ft_strjoin(folder, node->name);
//	char	*name = ft_strjoin(tmp, ".md");
//	free(tmp);
//	int fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
//	write(fd, "[[", 2);
//	ft_putstr_fd(G_Group_Identifier[num], fd);
//	write(fd, "]]\n", 3);
//	close(fd);
//	free(name);
//}

void	bonus()
{
	t_net	*net;
	t_list	*node;
	int		node_fd;
	char	*cwd;
	char	*temp;
	char	*filename;
	t_list	*link;

	net = *catch();
	node = net->graph_nodes;
	while (node)
	{
		temp = ft_strdup(((t_content *)((t_graph *)node->content)->content)->name);
		filename = ft_strjoin(temp, ".md");
		free(temp);
		cwd = ft_calloc(1024, 1);
		cwd = getcwd(cwd, 1023);
		if (!cwd)
			cut_loose();
		temp = ft_strjoin(cwd, "/bonus/Obsidian_Vault/");
		free(cwd);
		cwd = ft_strjoin(temp, filename);
		free (temp);
		free (filename);
		node_fd = open(cwd, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		free(cwd);
		link = ((t_graph *)node->content)->links;
		while (link)
		{
			if (((t_info *)((t_link *)link->content)->info)->active)
			{
				ft_putstr_fd("[[", node_fd);
				temp = ft_strdup(((t_content *)ft_otherside(link->content, node->content)->content)->name);
				filename = ft_strjoin(temp, ".md");
				free(temp);
				ft_putstr_fd(filename, node_fd);
				free(filename);
				ft_putstr_fd("]]\n", node_fd);
			}
			link = link->next;
		}
		if (((t_content *)((t_graph *)node->content)->content)->path > 0)
		{
			ft_putstr_fd("[[", node_fd);
			ft_putstr_fd(G_Group_Identifier[((t_content *)((t_graph *)node->content)->content)->path], node_fd);
			ft_putstr_fd("]]\n", node_fd);
		}
		node = node->next;
	}
}
