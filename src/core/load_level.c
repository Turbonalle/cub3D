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
	key_node_t	*tmp;

	count = 0;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			count++;
			tmp = tmp->next;
		}
		i++;
	}
	return (count);
}

void set_z_depth_of_all_images(cub3d_t *cub3d)
{
	int z;
	z = 0;
	
	cub3d->img->instances[0].z = z;
	printf("main img z: %d\n", cub3d->img->instances[0].z);
	z++;
	z += count_all_keys(cub3d);
	z += cub3d->num_enemies;
	cub3d->minimap.img->instances[0].z = z;
	printf("minimap z: %d\n", cub3d->minimap.img->instances[0].z);
	z++;
}

void	load_level(cub3d_t *cub3d, level_t *level)
{
	//TODO: handle init errors
	int	i = 0;

	level->map = ft_calloc(sizeof(char *), level->nodes + 1);
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
	init_textures(cub3d);
	set_z_depth_of_all_images(cub3d);
}
