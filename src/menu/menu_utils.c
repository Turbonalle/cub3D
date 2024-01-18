/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:26:24 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:52:09 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	pause_menu_helper(t_cub3d *cub3d, t_pause_menu *menu)
{
	menu->bg = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->bg)
		return (err("Failed to create image"));
	menu->menu = mlx_new_image(cub3d->mlx, cub3d->mlx->width * 0.5,
			cub3d->mlx->height * 0.9);
	if (!menu->menu)
		return (err("Failed to create image"));
	menu->title.img = mlx_texture_to_image(cub3d->mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create image"));
	menu->sensitivity_slider.marker = mlx_new_image(cub3d->mlx,
			SLIDER_MARKER_WIDTH, SLIDER_MARKER_HEIGHT);
	printf("put market to window in pause_menu_helper\n");
	if (!menu->sensitivity_slider.marker)
		return (err("Failed to create image"));
	return (SUCCESS);
}

void	delete_start_menu(t_cub3d *cub3d, t_start_menu *menu)
{
	mlx_delete_image(cub3d->mlx, menu->img);
	printf("deleting start menu title image. pointer: %p\n", menu->title.img);
	mlx_delete_image(cub3d->mlx, menu->title.img);
	mlx_delete_image(cub3d->mlx, menu->start.img);
	mlx_delete_image(cub3d->mlx, menu->level.img);
	mlx_delete_image(cub3d->mlx, menu->exit.img);
}

void	delete_level_menu(t_cub3d *cub3d, t_level_menu *menu)
{
	int	i;

	mlx_delete_image(cub3d->mlx, menu->img);
	mlx_delete_image(cub3d->mlx, menu->title.img);
	mlx_delete_image(cub3d->mlx, menu->back.img);
	mlx_delete_image(cub3d->mlx, menu->back_hover.img);
	mlx_delete_image(cub3d->mlx, menu->leaderboard.img);
	mlx_delete_image(cub3d->mlx, menu->leaderboard_hover.img);
	i = -1;
	while (++i < LEVELS)
	{
		mlx_delete_image(cub3d->mlx, menu->minilevels[i].img);
		mlx_delete_image(cub3d->mlx, menu->minilevels[i].number.img);
		mlx_delete_image(cub3d->mlx, menu->minilevels[i].border);
	}
}
