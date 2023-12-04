#include "../incl/cub3d.h"

void	load_level(cub3d_t *cub3d, level_t *level)
{
	int	i = 0;

	while (level->backup[i])
	{
		level->map[i] = ft_strdup(level->backup[i]);
		i++;
	}
	cub3d->player.pos.x = level->starting_pos.x + 0.5;
	cub3d->player.pos.y = level->starting_pos.y + 0.5;
	count_enemies(cub3d);
	if (cub3d->num_enemies > 0)
		init_enemy(cub3d);
	set_initial_direction(cub3d);
	init_minimap(cub3d);
	init_doors_and_keys(cub3d);
}
