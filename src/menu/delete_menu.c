/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:44 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 17:47:48 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	delete_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	record_t	*ptr;
	int			i;
	int			entry;

	i = 0;
	mlx_delete_image(cub3d->mlx, board->img);
	mlx_delete_image(cub3d->mlx, board->title.img);
	mlx_delete_image(cub3d->mlx, board->back.img);
	mlx_delete_image(cub3d->mlx, board->back_hover.img);
	while (++i < cub3d->n_levels + 1)
	{
		ptr = cub3d->levels[i].records;
		entry = -1;
		while (++entry < board->n_entries && ptr)
		{
			mlx_delete_image(cub3d->mlx, ptr->text_time);
			mlx_delete_image(cub3d->mlx, ptr->text_name);
			ptr = ptr->next;
		}
	}
}

void	delete_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	int	i;

	mlx_delete_image(cub3d->mlx, menu->img);
	mlx_delete_image(cub3d->mlx, menu->text_win_message);
	i = -1;
	while (++i < ALPHABET_LENGTH)
		mlx_delete_image(cub3d->mlx, menu->letters_img[i]);
}

void	delete_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	mlx_delete_image(cub3d->mlx, menu->bg);
	mlx_delete_image(cub3d->mlx, menu->menu);
	mlx_delete_image(cub3d->mlx, menu->text_title);
	mlx_delete_image(cub3d->mlx, menu->text_fps);
	mlx_delete_image(cub3d->mlx, menu->text_fisheye);
	mlx_delete_image(cub3d->mlx, menu->text_mouse);
	mlx_delete_image(cub3d->mlx, menu->box_fps[0].text);
	mlx_delete_image(cub3d->mlx, menu->box_fps[1].text);
	mlx_delete_image(cub3d->mlx, menu->box_fps[2].text);
	mlx_delete_image(cub3d->mlx, menu->box_fps[3].text);
	mlx_delete_image(cub3d->mlx, menu->box_fisheye[0].text);
	mlx_delete_image(cub3d->mlx, menu->box_fisheye[1].text);
	mlx_delete_image(cub3d->mlx, menu->box_mouse[0].text);
	mlx_delete_image(cub3d->mlx, menu->box_mouse[1].text);
}

void	delete_menus(cub3d_t *cub3d)
{
	delete_start_menu(cub3d, &cub3d->start_menu);
	delete_level_menu(cub3d, &cub3d->level_menu);
	delete_leaderboard(cub3d, &cub3d->leaderboard);
	delete_name_menu(cub3d, &cub3d->name_menu);
	delete_pause_menu(cub3d, &cub3d->pause_menu);
}
