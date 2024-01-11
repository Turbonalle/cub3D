/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_name_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:37:29 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 19:54:13 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	disable_name_menu(mlx_t *mlx, name_menu_t *menu)
{
	int	letter;
	int	index;

	mlx_delete_image(mlx, menu->text_time);
	menu->img->instances[0].enabled = FALSE;
	menu->title_win.img->instances[0].enabled = FALSE;
	menu->title_top3.img->instances[0].enabled = FALSE;
	menu->back.img->instances[0].enabled = FALSE;
	menu->back_hover.img->instances[0].enabled = FALSE;
	menu->timer.img->instances[0].enabled = FALSE;
	while (menu->current > 0)
	{
		menu->current--;
		letter = menu->name[menu->current] - 'a';
		index = menu->letter_index[menu->current];
		menu->letters_img[letter]->instances[index].enabled = FALSE;
		menu->name[menu->current] = '\0';
	}
}

void	reset_name_menu(name_menu_t *menu)
{
	int	i;

	menu->current = 0;
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->box[i].letter[0] = '\0';
}

void	enable_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	create_time_string(menu->time_str, cub3d->time_finished);
	menu->text_time = mlx_put_string(cub3d->mlx, menu->time_str,
			menu->timer.pos.x + menu->timer.img->width * 0.5,
			menu->timer.pos.y + menu->timer.img->height + 10);
	center_horizontally(menu->text_time);
	reset_name_menu(menu);
	menu->img->instances[0].enabled = TRUE;
	menu->title_win.img->instances[0].enabled = TRUE;
	menu->title_top3.img->instances[0].enabled = TRUE;
	menu->back.img->instances[0].enabled = TRUE;
	menu->back_hover.img->instances[0].enabled = FALSE;
	menu->timer.img->instances[0].enabled = TRUE;
}
