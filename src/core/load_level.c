/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:20:00 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/19 15:42:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	init_player_and_enemies(t_cub3d *cub3d, t_level *level)
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
		return (FAIL);
	return (SUCCESS);
}

static int	free_half_done(t_cub3d *cub3d, t_level *level, int i)
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
	return (FAIL);
}

static int	fill_backup(t_level *level)
{
	int	i;

	i = 0;
	while (level->backup[i])
	{
		level->map[i] = ft_strdup(level->backup[i]);
		if (!level->map[i])
			return (free_info(level->map), FAIL);
		i++;
	}
	return (SUCCESS);
}

int	load_level(t_cub3d *cub3d, t_level *level)
{
	level->map = ft_calloc(sizeof(char *), level->nodes + 1);
	if (!level->map)
		return (FAIL);
	if (!fill_backup(level))
		return (FAIL);
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
	return (SUCCESS);
}
