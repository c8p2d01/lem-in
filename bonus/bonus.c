#include "../inc/lem_in.h"
#include "bonus.h"

char	*G_Group_Identifier[47] = {
	"In einem ",
	"Bächlein helle,",
	"Da schoß in",
	"froher Eil",
	"Die launische",
	"Forelle",
	"Vorüber, wie",
	"ein Pfeil:",
	"Ich stand",
	"an dem Gestade",
	"Und sah in",
	"süßer Ruh",
	"Des muntern",
	"Fischleins Bade",
	"Im klaren",
	"Bächlein zu.",
	"Ein Fischer",
	"mit der Ruthe",
	"Wol an dem",
	"Ufer stand,",
	"Und sahs mit",
	"kaltem Blute,",
	"Wie sich das",
	"Fischlein wand.",
	"So lang dem",
	"Wasser Helle,",
	"So dacht ich,",
	"nicht gebricht,",
	"So fängt er",
	"die Forelle",
	"Mit seiner",
	"Angel nicht.",
	"Doch endlich",
	"ward dem Diebe",
	"Die Zeit zu",
	"lang; er macht",
	"Das Bächlein",
	"tückisch trübe:",
	"Und eh ich",
	"es gedacht,",
	"So zuckte",
	"seine Ruthe;",
	"Das Fischlein",
	"zappelt dran;",
	"Und ich, mit",
	"regem Blute,",
	"Sah die Betrogne an."
};



void	assignColorToPath(globe *data, char **env)
{
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

	int fd = open(folder, O_RDWR | O_TRUNC);
	
	char	*tmp = ft_itoa(createGradientColor(1, 255, 255, 255, 0, 0, 0));
	ft_printf_fd(fd, "%s%s%s%s%s%s%s%s%s",
				"{\n",
				"  \"collapse-filter\": false,\n",
				"  \"search\": \"\",\n",
				"  \"showTags\": false,\n",
				"  \"showAttachments\": false,\n",
				"  \"hideUnresolved\": false,\n",
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

	int		nPath = ft_array_size((void *)data->paths);
	for (int i = 0; i < nPath; i++)
	{
		// char	*pathnumber;
		char	*tmp = ft_itoa(createMultiGradient(((float)i / (float)nPath), 7, 255,0,0, 255,0,255, 0,0,255, 0,255,255, 0,255,0, 255,255,0, 255,0,0));
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

void	bonus(globe *data, char **env)
{
	(void)data;
	assignColorToPath(data, env);
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
	for(int i = 0; data->paths[i]; i++)
	{
		for(int p = 0; data->paths[i]->path[p]; p++)
		{
			pathnodefile(data->paths[i]->path[p], folder, data, data->paths[i]);
			pathfile(data->paths[i]->path[p], folder, i);
		}
	}
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
	char	*name = ft_strjoin(tmp, ".md");
	free(tmp);
	int fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	write(fd, "[[", 2);
	ft_putstr_fd(G_Group_Identifier[num], fd);
	write(fd, "]]\n", 3);
	close(fd);
	free(name);
}
