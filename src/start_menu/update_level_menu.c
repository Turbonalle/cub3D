#include "../incl/cub3d.h"

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
	get_transition_color(cub3d, &menu->background_color);
	draw_menu_background(menu->img, menu->background_color);
	draw_rectangle(menu->img, &menu->rect_title);
	check_level_button_hover(cub3d, menu);
	int i;

	i = -1;
	while (++i < 9)
		draw_button(menu->img, &menu->buttons[i]);
	draw_button(menu->img, &menu->button_back);
	draw_button(menu->img, &menu->button_leaderboard);
}