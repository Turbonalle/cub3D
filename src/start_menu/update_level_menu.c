#include "../incl/cub3d.h"

void	draw_minimap_preview(mlx_image_t *img, button_t *button, level_t *level)
{
	int	width;
	int	height;
	int	square_size;
	int	row;
	int	column;
	int	margin;

	width = button->width;
	height = button->height;
	square_size = min(width / level->map_columns, height / level->map_rows);
	margin = (width - square_size * level->map_columns) / 2;

	row = -1;
	while (++row < level->map_rows)
	{
		column = -1;
		while (++column < level->map_columns)
		{
			if (level->backup[row][column] == '1')
				draw_square(img, button->pos.x + margin + column * square_size, button->pos.y + row * square_size, square_size, GRAY_LIGHT);
			else
				draw_square(img, button->pos.x + margin + column * square_size, button->pos.y + row * square_size, square_size, MINIMAP_COLOR_EMPTY);
		}
	}
}

void	check_level_button_hover(cub3d_t *cub3d, level_menu_t *menu)
{
	int	mouse_x;
	int	mouse_y;
	int	i;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	i = -1;
	while (++i < 9)
	{
		if (hover_button(cub3d, &menu->buttons[i]))
			menu->buttons[i].background_color = BUTTON_HOVER_COLOR;
		else
			menu->buttons[i].background_color = BUTTON_COLOR;
	}
	if (hover_button(cub3d, &menu->button_back))
		menu->button_back.background_color = BUTTON_HOVER_COLOR;
	else
		menu->button_back.background_color = BUTTON_COLOR;
	if (hover_button(cub3d, &menu->button_leaderboard))
		menu->button_leaderboard.background_color = BUTTON_HOVER_COLOR;
	else
		menu->button_leaderboard.background_color = BUTTON_COLOR;
}

void	update_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	int	i;

	get_transition_color(cub3d, &menu->background_color);
	draw_menu_background(menu->img, menu->background_color);
	draw_rectangle(menu->img, &menu->rect_title);
	// check_level_button_hover(cub3d, menu);
	i = -1;
	while (++i < cub3d->n_levels)
		draw_minimap_preview(menu->img, &menu->buttons[i], &cub3d->levels[i + 1]);
	// 	draw_button(menu->img, &menu->buttons[i]);
	draw_button(menu->img, &menu->button_back);
	draw_button(menu->img, &menu->button_leaderboard);
}
