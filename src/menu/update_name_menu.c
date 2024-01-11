/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_name_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:22:28 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 17:22:30 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	update_letter(mlx_t *mlx, name_menu_t *menu, int *key, int i)
{
	*key = FALSE;
	menu->name[menu->current] = i + 'a';
	menu->letter_index[menu->current] = mlx_image_to_window(mlx,
			menu->letters_img[i], menu->box[menu->current].pos.x
			+ menu->box[menu->current].width * 0.5,
			menu->box[menu->current].pos.y
			+ menu->box[menu->current].height * 0.5);
	menu->letters_img[i]->instances[menu->letter_index[menu->current]].x
		-= menu->letters_img[i]->width * 0.5;
	menu->letters_img[i]->instances[menu->letter_index[menu->current]].y
		-= menu->letters_img[i]->height * 0.5;
	if (menu->current < MAX_NAME_LENGTH)
		menu->current++;
	print_letter_indexes(menu, 0);
	return (1);
}

int	name_is_empty(name_menu_t *menu)
{
	return (menu->name[0] == '\0');
}

void	submit_name(cub3d_t *cub3d, name_menu_t *menu)
{
	int	i;

	remove_record_image_pointers(cub3d);
	if (name_is_empty(menu))
	{
		add_record(cub3d, &cub3d->level->records, cub3d->time_finished,
			ft_strdup("Anonymous"), cub3d->leaderboard.n_entries);
	}
	else
	{
		add_record(cub3d, &cub3d->level->records, cub3d->time_finished,
			ft_strdup(menu->name), cub3d->leaderboard.n_entries);
	}
	i = get_current_level(cub3d);
	draw_names(cub3d->mlx, &cub3d->level->records, &cub3d->leaderboard, i);
	draw_times(cub3d->mlx, &cub3d->level->records, &cub3d->leaderboard, i);
}

void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		menu->back.img->instances[0].enabled = FALSE;
		menu->back_hover.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->back.img->instances[0].enabled = TRUE;
		menu->back_hover.img->instances[0].enabled = FALSE;
	}
	if (menu->changed == TRUE)
	{
		if (change_name(cub3d, menu))
			return ;
	}
}
