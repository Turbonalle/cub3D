#include "../incl/cub3d.h"

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
			cub3d->level->key_groups[i]
				.img_key_icon->instances[0].z = starting_z;
			starting_z++;
			// if malloc fails at draw_key_count this will segfault
			cub3d->level->key_groups[i]
				.img_text_key_count->instances[0].z = starting_z;
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
	z += cub3d->level->num_distractions;
	z += set_z_for_key_groups(cub3d, z);
	cub3d->minimap.img->instances[0].z = z;
	//cub3d->timer.img_time->instances[0].z = z;
	//printf("timer z: %d\n", cub3d->timer.img_time->instances[0].z);
	//TODO: think about menus
	z++;
	//printf("LAST z: %d\n", z);
}
int	init_player_and_enemies(cub3d_t *cub3d, level_t *level)
{
	cub3d->player.pos.x = level->starting_pos.x + 0.5;
	cub3d->player.pos.y = level->starting_pos.y + 0.5;
	cub3d->player.mushroom_count = 0;
	cub3d->level->distraction_amount = 0;
	cub3d->player.health = HEARTS;
	cub3d->player.thrown = FALSE;
	cub3d->player.is_dirty_cheater = 0;
	count_enemies(cub3d);
	if (!init_enemy(cub3d))
		return (0);
	return (1);
}

int	load_level(cub3d_t *cub3d, level_t *level)
{
	//TODO: handle init errors
	int	i = 0;

	level->map = ft_calloc(sizeof(char *), level->nodes + 1);
	if (!level->map)
		return (FAIL);
	while (level->backup[i])
	{
		level->map[i] = ft_strdup(level->backup[i]);
		if (!level->map[i])
			return (free_info(level->map), FAIL);
		i++;
	}
	if (!init_player_and_enemies(cub3d, level))
	{
		free_info(level->map);
		return (FAIL);
	}
	count_distractions(cub3d);
	if (!init_distractions(cub3d))
	// We probably should remove free_level calls from this function because we're freeing things that haven't been allocated yet
		return (free_info(level->map), FAIL);
	set_initial_direction(cub3d);
	if (!init_minimap(cub3d))
		return (free_distractions(cub3d), free_info(level->map), FAIL);
	if (!init_doors_and_keys(cub3d))
	{
		// TODO: make sure error handling and freeing inside init_doors_and_keys is good
		free_info(level->map);
		free_enemies(cub3d);
		free_distractions(cub3d);
		free_minimap(cub3d);
		return (0);
	}
	printf("LOAD before init textures\n");
	// if (!init_textures(cub3d))
	// 	return (free_level_without_textures(cub3d), FAIL);
	printf("LOAD after init textures\n");
	set_z_of_all_images(cub3d);
	//printf("after set_z_of_all_images\n");
	enable_hearts(cub3d);
	printf("LOAD after enable_hearts\n");
	return (SUCCESS);
}
