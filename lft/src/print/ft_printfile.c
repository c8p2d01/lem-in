#include "../../inc/libft.h"

void printfile(int fd)
{
	char	*line = NULL;
	int c = 0;

	while ((c = get_next_line(fd, &line)) != 0)
		printf("%s\n", line);
}
