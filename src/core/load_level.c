#include "../incl/cub3d.h"

int	key_list_len(key_node_t	*keys)
{
	int	count;

	count = 0;
	while (keys)
	{
		count++;
		keys = keys->next;
	}
	return (count);
}

int	count_all_keys(cub3d_t *cub3d)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		count += cub3d->level->key_groups[i].num_keys_total;
		i++;
	}
	return (count);
}

int	set_z_for_key_groups(cub3d_t *cub3d, int starting_z)
{
	int			i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->key_groups[i].num_keys_total)
		{
			cub3d->level->key_groups[i].img_key_icon->instances[0].z = starting_z;
			starting_z++;
			cub3d->level->key_groups[i].img_text_key_count->instances[0].z = starting_z;
			starting_z++;
		}
		i++;
	}
	return (starting_z);
}

void	set_z_of_all_images(cub3d_t *cub3d)
{
	int	z;

	z = 0;
	cub3d->img->instances[0].z = z;
	z++;
	z += count_all_keys(cub3d);
	z += cub3d->num_enemies;
	cub3d->minimap.img->instances[0].z = z;
	z = set_z_for_key_groups(cub3d, z);
	//cub3d->timer.img_time->instances[0].z = z;
	//printf("timer z: %d\n", cub3d->timer.img_time->instances[0].z);
	//TODO: think about menus
	z++;
}

int	load_level(cub3d_t *cub3d, level_t *level)
{
	//TODO: handle init errors
	int	i = 0;

	level->map = ft_calloc(sizeof(char *), level->nodes + 1);
	while (level->backup[i])
	{
		level->map[i] = ft_strdup(level->backup[i]);
		if (!level->map[i])
		{
			return (free_info(level->map), 0);
		}
		i++;
	}
	cub3d->player.pos.x = level->starting_pos.x + 0.5;
	cub3d->player.pos.y = level->starting_pos.y + 0.5;
	cub3d->player.mushroom_count = 0;
	cub3d->level->distraction_amount = 0;
	cub3d->player.health = PLAYER_HEALTH;
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
	set_z_of_all_images(cub3d);
	enable_hearts(cub3d);
	return (1);
}
