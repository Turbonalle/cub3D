#include "../incl/cub3d.h"

int	load_level(cub3d_t *cub3d, level_t *level)
{
	//TODO: handle init errors
	int	i = 0;

	level->map = ft_calloc(sizeof(char *), level->nodes + 1);
	while (level->backup[i])
	{
		level->map[i] = ft_strdup(level->backup[i]);
		if (!level->map[i])
			return (free_info(level->map), 0);
		i++;
	}
	cub3d->player.pos.x = level->starting_pos.x + 0.5;
	cub3d->player.pos.y = level->starting_pos.y + 0.5;
	cub3d->player.mushroom_count = 0;
	cub3d->level->distraction_amount = 0;
	count_enemies(cub3d);
	if (cub3d->num_enemies > 0)
	{
		if (!init_enemy(cub3d))
			return (0);
	}
	set_initial_direction(cub3d);
	if (!init_minimap(cub3d))
		return (free_info(level->map), free(cub3d->enemy), 0);
	init_doors_and_keys(cub3d);
	init_textures(cub3d);
	return (1);
}
