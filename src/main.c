#include "../inc/lem_in.h"

int main()
{
	globe data;
	ft_bzero(&data, sizeof(globe));
	readData(&data);

	//level(&data);

	//print_nodes(data.allNodes);



	freeGlobe(&data);
}
