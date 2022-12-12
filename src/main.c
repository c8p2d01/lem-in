#include "../inc/lem_in.h"

int main()
{
	globe data;
	data.nAnts = 0;
	data.allNodes = NULL;
	readData(&data);

	printNode(data.start);
	freeGlobe(&data);
}
