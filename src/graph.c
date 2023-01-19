#include "../inc/lem_in.h"

/**
 * @brief Free globe struct
 */
void	freeGlobe(globe *data)
{
	for (size_t i = 0; data->allNodes && data->allNodes[i] != NULL; ++i)
	{
		if (data->allNodes[i]->name)
			free(data->allNodes[i]->name);
		if (data->allNodes[i]->gates)
			free(data->allNodes[i]->gates);
		free(data->allNodes[i]);
	}
	if (data->allNodes)
		free(data->allNodes);
}
