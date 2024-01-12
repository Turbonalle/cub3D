#include "../incl/cub3d.h"

void	nullify_level(level_t *level)
{
	int	i;

	level->map = NULL;
	level->backup = NULL;
	level->map_list = NULL;
	level->records = NULL;
	level->distractions = NULL;
	i = -1;
	while (++i < 4)
		nullify_texture(&level->texture[i]);
}