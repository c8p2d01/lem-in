#ifndef BONUS_H
# define BONUS_H

# ifndef TEST
#  define TEST true
# endif

void	bonus(globe *data, char **env);
void	pathnodefile(t_room *node, char *folder, globe *data, t_path *path);
void	nodefile(t_room *node, char *folder, globe *data);

#endif
