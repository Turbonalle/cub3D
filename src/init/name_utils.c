/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:22:45 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	free_prev_name_menu(t_name_menu *menu, int i)
{
	mlx_delete_texture(menu->timer.texture);
	if (i > 0)
		mlx_delete_texture(menu->back.texture);
	if (i > 1)
		mlx_delete_texture(menu->back_hover.texture);
	return (FAIL);
}

void	draw_letter_box(mlx_image_t *img, t_letter_box *box)
{
	int	col;
	int	row;

	row = box->pos.y - 1;
	while (++row < box->height + box->pos.y)
	{
		col = box->pos.x - 1;
		while (++col < box->width + box->pos.x)
		{
			if (row < box->pos.y + box->border_width || row >= box->pos.y
				+ box->width - box->border_width)
				mlx_put_pixel(img, col, row, box->border_color);
			else if (col < box->pos.x + box->border_width || col >= box->pos.x
				+ box->width - box->border_width)
				mlx_put_pixel(img, col, row, box->border_color);
			else
				mlx_put_pixel(img, col, row, box->background_color);
		}
	}
}

void	init_letter_images(t_cub3d *cub3d, t_name_menu *menu)
{
	int	i;

	i = -1;
	while (++i < ALPHABET_LENGTH)
	{
		menu->letter_str[i][0] = ALPHABET[i];
		menu->letter_str[i][1] = '\0';
		menu->letters_img[i]
			= mlx_put_string(cub3d->mlx, menu->letter_str[i], 0, 0);
		menu->letters_img[i]->instances[0].enabled = FALSE;
	}
}

void	set_letter_fields(t_name_menu *menu)
{
	int	i;

	i = -1;
	while (++i < MAX_NAME_LENGTH)
	{
		menu->box[i].width = (menu->rect_input.width
				- (NAME_BOX_GAP * (MAX_NAME_LENGTH - 1))) / MAX_NAME_LENGTH;
		menu->box[i].height = menu->rect_input.height;
		menu->box[i].pos.x = menu->rect_input.pos.x + i
			* menu->box[i].width + i * NAME_BOX_GAP;
		menu->box[i].pos.y = menu->rect_input.pos.y;
		menu->box[i].background_color = BOX_OFF_COLOR;
		menu->box[i].border_color = BOX_BORDER_COLOR;
		menu->box[i].border_width = 1;
		menu->box[i].letter[0] = '\0';
		menu->box[i].letter[1] = '\0';
	}
}

void	init_name_values(t_name_menu *menu)
{
	int	i;

	i = -1;
	while (++i < MAX_NAME_LENGTH)
	{
		menu->name[i] = '\0';
		menu->letter_index[i] = 0;
	}
	menu->changed = FALSE;
	menu->current = 0;
}
