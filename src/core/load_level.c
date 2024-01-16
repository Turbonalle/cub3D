/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:20:00 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 11:03:20 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	z++;
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

int	free_half_done(cub3d_t *cub3d, level_t *level, int i)
{
	free_info(level->map);
	if (i > 0)
		free_enemies(cub3d);
	if (i > 1)
		free_distractions(cub3d);
	if (i > 2)
		free_minimap(cub3d);
	if (i == 0)
		return (err("Failed to init player and enemies"));
	if (i == 1)
		return (err("Failed to init distractions"));
	if (i == 2)
		return (err("Failed to init minimap"));
	if (i == 3)
		return (err("Failed to init doors or keys"));
	return (0);
}

int	load_level(cub3d_t *cub3d, level_t *level)
{
	int	i;

	i = 0;
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
		return (free_half_done(cub3d, level, 0));
	count_distractions(cub3d);
	if (!init_distractions(cub3d))
		return (free_half_done(cub3d, level, 1));
	set_initial_direction(cub3d);
	if (!init_minimap(cub3d))
		return (free_half_done(cub3d, level, 2));
	if (!init_doors_and_keys(cub3d))
		return (free_half_done(cub3d, level, 3));
	set_z_of_all_images(cub3d);
	enable_hearts(cub3d);
	printf("LOAD after enable_hearts\n");
	return (SUCCESS);
}
