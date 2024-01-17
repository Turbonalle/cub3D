/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_freeing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:53:39 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:55:54 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_enemy_frames(cub3d_t *cub3d)
{
	int	j;
	int	i;

	j = 0;
	while (j < NUM_ENEMY_DIRECTIONS)
	{
		i = 0;
		while (i < NUM_FRAMES_ENEMY_IDLE)
		{
			if (cub3d->frames_idle[j][i])
				mlx_delete_texture(cub3d->frames_idle[j][i]);
			i++;
		}
		i = 0;
		while (i < NUM_FRAMES_ENEMY_WALKING)
		{
			if (cub3d->frames_walking[j][i])
				mlx_delete_texture(cub3d->frames_walking[j][i]);
			i++;
		}
		j++;
	}
}

int	handle_message_extra(int i)
{
	if (i == 12)
		return (err("Failed to load mushroom texture"));
	if (i == 13)
		return (err("Failed to load door textures"));
	if (i == 14)
		return (err("Failed to load goal textures"));
	if (i == 15)
		return (err("Failed to init pause menu"));
	if (i == 16)
		return (err("Failed to read records"));
	if (i == 17)
		return (err("Failed to init leaderboard"));
	if (i == 18)
		return (err("Failed to init enemy_frames"));
	if (i == 19)
		return (err("Failed to init floor"));
	return (1);
}

int	handle_message(int i)
{
	if (i == 0)
		return (err("Failed to initialize mlx"));
	if (i == 1)
		return (err("Failed to create image"));
	if (i == 2)
		return (err("Failed to malloc rays"));
	if (i == 3)
		return (err("Failed to init start menu"));
	if (i == 4)
		return (err("Failed to init level menu"));
	if (i == 5)
		return (err("Failed to init name menu"));
	if (i == 6)
		return (err("Failed to init gameover menu"));
	if (i == 7)
		return (err("Failed to init intro"));
	if (i == 8)
		return (err("Failed to init hearts"));
	if (i == 9)
		return (err("Failed to init shroom counter"));
	if (i == 10)
		return (err("Failed to init halo"));
	if (i == 11)
		return (err("Failed to load mushroom thrown texture"));
	return (handle_message_extra(i));
}

static void	free_levels(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < LEVELS + 1)
	{
		free_list(cub3d->levels[i].map_list);
		free_backup(cub3d->levels[i]);
		i++;
	}
	free(cub3d->levels);
}

int	free_all(cub3d_t *cub3d, int i)
{
	free_records(cub3d);
	free_levels(cub3d);
	if (cub3d->rays)
		free(cub3d->rays);
	free_start_menu(&cub3d->start_menu);
	free_level_menu(&cub3d->level_menu);
	free_name_menu(&cub3d->name_menu);
	free_gameover_menu(&cub3d->gameover_menu);
	free_intro(cub3d);
	free_hearts(cub3d);
	free_shroom(cub3d);
	free_door_textures(cub3d);
	free_star_textures(cub3d);
	free_pause_menu(&cub3d->pause_menu);
	free_leaderboard(&cub3d->leaderboard);
	free_enemy_frames(cub3d);
	if (cub3d->floor.texture)
		mlx_delete_texture(cub3d->floor.texture);
	return (handle_message(i));
}
