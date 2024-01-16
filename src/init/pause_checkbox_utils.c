/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_checkbox_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:12:34 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 15:15:33 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	init_checkbox_info(pause_menu_t *menu, box_t *box, int pos_x, int pos_y)
{
	box->pos.x = pos_x - menu->menu_pos.x;
	box->pos.y = pos_y - menu->menu_pos.y;
	box->size = menu->menu->width * 0.08;
	box->border_width = fmax(box->size * 0.02, 2);
	box->border_color = BOX_BORDER_COLOR;
}

void	init_checkboxes(pause_menu_t *menu)
{
	init_checkbox_info(menu, &menu->box_fps[0], menu->pos_col_box_1,
		menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fps[1], menu->pos_col_box_2,
		menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fps[2], menu->pos_col_box_3,
		menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fps[3], menu->pos_col_box_4,
		menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fisheye[0], menu->pos_col_box_1,
		menu->pos_row_2);
	init_checkbox_info(menu, &menu->box_fisheye[1], menu->pos_col_box_2,
		menu->pos_row_2);
	init_checkbox_info(menu, &menu->box_mouse[0], menu->pos_col_box_1,
		menu->pos_row_3);
	init_checkbox_info(menu, &menu->box_mouse[1], menu->pos_col_box_2,
		menu->pos_row_3);
}

void	set_checkbox_values(pause_menu_t *menu)
{
	menu->box_fps[0].value = 15;
	menu->box_fps[1].value = 30;
	menu->box_fps[2].value = 60;
	menu->box_fps[3].value = 120;
	menu->box_fisheye[0].value = ON;
	menu->box_fisheye[1].value = OFF;
	menu->box_mouse[0].value = ON;
	menu->box_mouse[1].value = OFF;
}

void	init_checkbox_states(pause_menu_t *menu)
{
	menu->box_fps[0].state = FALSE;
	menu->box_fps[1].state = FALSE;
	menu->box_fps[2].state = TRUE;
	menu->box_fps[3].state = FALSE;
	menu->box_fisheye[0].state = FALSE;
	menu->box_fisheye[1].state = TRUE;
	menu->box_mouse[0].state = FALSE;
	menu->box_mouse[1].state = TRUE;
}
