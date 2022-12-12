#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));
	readData(&data);

	printNodes(data.allNodes);
	freeGlobe(&data);
}
