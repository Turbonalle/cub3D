/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:20:00 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/19 14:39:21 by jbagger          ###   ########.fr       */
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
	// printf("init_player_and_enemies: count_enemies()\n");
	count_enemies(cub3d);
	// printf("init_player_and_enemies: init_enemy()\n");
	if (!init_enemy(cub3d))
	{
		// printf("init_player_and_enemies: return FAIL\n");
		return (FAIL);
	}
	// printf("init_player_and_enemies: return SUCCESS\n");
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
	// printf("fill_backup: while (level->backup[i])\n");
	while (level->backup[i])
	{
		// printf("fill_backup: ft_strdup(level->backup[%d])\n", i);
		level->map[i] = ft_strdup(level->backup[i]);
		// printf("fill_backup: checking if level->map[%d] is NULL\n", i);
		if (!level->map[i])
		{
			// printf("fill_backup: free_info(level->map)\n");	
			return (free_info(level->map), FAIL);
		}
		i++;
	}
	// printf("fill_backup: return SUCCESS\n");
	return (SUCCESS);
}

int	load_level(t_cub3d *cub3d, t_level *level)
{
	// printf("load_level: ft_calloc()");
	level->map = ft_calloc(sizeof(char *), level->nodes + 1);
	// printf("load_level: checking if level->map is NULL\n");
	if (!level->map)
		return (FAIL);
	// printf("load_level: fill_backup()");
	if (!fill_backup(level))
		return (FAIL);
	// printf("load_level: init_player_and_enemies()");
	if (!init_player_and_enemies(cub3d, level))
	{
		// printf("load_level: init_player_and_enemies FAILED\n");
		return (free_half_done(cub3d, level, 0));
	}
	// printf("load_level: count_distractions()");
	count_distractions(cub3d);
	// printf("load_level: init_distractions()");
	if (!init_distractions(cub3d))
	{
		// printf("load_level: init_distractions FAILED\n");	
		return (free_half_done(cub3d, level, 1));
	}
	// printf("load_level: set_initial_direction()");
	set_initial_direction(cub3d);
	// printf("load_level: init_minimap()");
	if (!init_minimap(cub3d))
		return (free_half_done(cub3d, level, 2));
	if (!init_doors_and_keys(cub3d))
		return (free_half_done(cub3d, level, 3));
	// printf("load_level: set_z_of_all_images()");
	set_z_of_all_images(cub3d);
	// printf("load_level: set_health()\n");
	set_health(cub3d);
	// printf("load_level: adjust_hearts()\n");
	adjust_hearts(cub3d);
	// printf("load_level: return SUCCESS\n");
	return (SUCCESS);
}
