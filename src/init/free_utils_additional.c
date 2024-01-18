/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_additional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:53:39 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:11:16 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_leaderboard(t_leaderboard *board)
{
	if (board->title.texture)
		mlx_delete_texture(board->title.texture);
	if (board->back.texture)
		mlx_delete_texture(board->back.texture);
	if (board->back_hover.texture)
		mlx_delete_texture(board->back_hover.texture);
}

void	free_shroom(t_cub3d *cub3d)
{
	if (cub3d->shroom && cub3d->shroom->shroom.texture)
		mlx_delete_texture(cub3d->shroom->shroom.texture);
	if (cub3d->shroom)
		free(cub3d->shroom);
	if (cub3d->distraction_texture)
		mlx_delete_texture(cub3d->distraction_texture);
	if (cub3d->distraction_thrown_texture)
		mlx_delete_texture(cub3d->distraction_thrown_texture);
}

void	free_door_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (cub3d->door[i].texture)
			mlx_delete_texture(cub3d->door[i].texture);
		i++;
	}
}

void	free_star_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_FRAMES_STARS)
	{
		if (cub3d->stars[i].texture)
			mlx_delete_texture(cub3d->stars[i].texture);
		if (cub3d->stars[i].path)
			free(cub3d->stars[i].path);
		i++;
	}
}

void	free_pause_menu(t_pause_menu *menu)
{
	if (menu->title.texture)
		mlx_delete_texture(menu->title.texture);
}
