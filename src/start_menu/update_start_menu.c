#include "../incl/cub3d.h"

void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	if (hover_image(cub3d, menu->exit.img))
	{
		menu->exit_hover.img->instances[0].enabled = TRUE;
		menu->exit.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->exit_hover.img->instances[0].enabled = FALSE;
		menu->exit.img->instances[0].enabled = TRUE;
	}
	if (hover_image(cub3d, menu->start.img))
	{
		menu->start_hover.img->instances[0].enabled = TRUE;
		menu->start.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->start_hover.img->instances[0].enabled = FALSE;
		menu->start.img->instances[0].enabled = TRUE;
	}
	if (hover_image(cub3d, menu->level.img))
	{
		menu->level_hover.img->instances[0].enabled = TRUE;
		menu->level.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->level_hover.img->instances[0].enabled = FALSE;
		menu->level.img->instances[0].enabled = TRUE;
	}
}

void	get_transition_color(cub3d_t *cub3d, int *color)
{
	double	time;

	time = mlx_get_time() - cub3d->start_timestamp;

    double frequency = 0.1; // Adjust the frequency of the sine wave
    double amplitude = 0.1; // Adjust the amplitude of the sine wave
    double colorShift = 0.1;  // Adjust the shift for the color channel

    double sineValue = sin(2.0 * M_PI * frequency * time);

	int intensity = (int)((amplitude * sineValue + colorShift) * 255);
	*color = set_rgba(20, 20 + intensity  * 0.8, 20 + intensity, 255);
}

// void	check_button_hover(cub3d_t *cub3d, start_menu_t *menu)
// {
// 	int	mouse_x;
// 	int	mouse_y;

// 	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
// 	if (hover_button(cub3d, &menu->button_start))
// 		menu->button_start.background_color = BUTTON_HOVER_COLOR;
// 	else
// 		menu->button_start.background_color = BUTTON_COLOR;
// 	if (hover_button(cub3d, &menu->button_level))
// 		menu->button_level.background_color = BUTTON_HOVER_COLOR;
// 	else
// 		menu->button_level.background_color = BUTTON_COLOR;
// 	if (hover_button(cub3d, &menu->button_settings))
// 		menu->button_settings.background_color = BUTTON_HOVER_COLOR;
// 	else
// 		menu->button_settings.background_color = BUTTON_COLOR;
// 	if (hover_button(cub3d, &menu->button_exit))
// 		menu->button_exit.background_color = BUTTON_HOVER_COLOR;
// 	else
// 		menu->button_exit.background_color = BUTTON_COLOR;
// }

// void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu)
// {
// 	get_transition_color(cub3d, &menu->background_color);
// 	draw_menu_background(menu->img, menu->background_color);
// 	draw_rectangle(menu->img, &menu->rect_title);
// 	check_button_hover(cub3d, menu);
// 	draw_button(menu->img, &menu->button_start);
// 	draw_button(menu->img, &menu->button_level);
// 	draw_button(menu->img, &menu->button_settings);
// 	draw_button(menu->img, &menu->button_exit);
// }
