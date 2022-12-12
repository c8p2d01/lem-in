#include "../inc/lem_in.h"

int main()
{
	gNode *start = ft_gNewNode("start");
	gNode *end = ft_gNewNode("end");
	gNode *a = ft_gNewNode("a");
	gNode *b = ft_gNewNode("b");
	gNode *c = ft_gNewNode("c");
	ft_gInsert(start, 2, a, end);
	ft_gInsert(a, 1, end);
	printNode(start);
	printNode(a);
	printf("debug\n");
	printf("end\n\t%s\n\t%p\n", end->name, end);
	printf("start\n\t%s\n\t%p\n", start->name, start);
	printf("a\n\t%s\n\t%p\n", a->name, a);
	printf("end gates\n\t%p\n\t%p\n\t%p\n", end->gates, end->gates[0], end->gates[1], end->gates[2]);
	printf("a gates\n\t%p\n\t%p\n\t%p\n", a->gates, a->gates[0], a->gates[1], a->gates[2]);
	printf("debug\n");
	printNode(end);
}