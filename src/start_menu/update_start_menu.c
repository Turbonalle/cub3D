#include "../incl/cub3d.h"

void	get_transition_color(cub3d_t *cub3d, int *color)
{
	double	time;

	time = mlx_get_time() - cub3d->start_time;

    double frequency = 0.1; // Adjust the frequency of the sine wave
    double amplitude = 0.1; // Adjust the amplitude of the sine wave
    double colorShift = 0.1;  // Adjust the shift for the color channel

    double sineValue = sin(2.0 * M_PI * frequency * time);

    int intensity = (int)((amplitude * sineValue + colorShift) * 255);

	*color = set_rgba(0, intensity, 0, 255);
}

void	check_button_hover(cub3d_t *cub3d, start_menu_t *menu)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	if (mouse_x >= menu->button_start.pos.x
		&& mouse_x <= menu->button_start.pos.x + menu->button_start.width
		&& mouse_y >= menu->button_start.pos.y
		&& mouse_y <= menu->button_start.pos.y + menu->button_start.height)
	{
		menu->button_start.background_color = BUTTON_HOVER_COLOR;
	}
	else
		menu->button_start.background_color = BUTTON_COLOR;

	if (mouse_x >= menu->button_settings.pos.x
		&& mouse_x <= menu->button_settings.pos.x + menu->button_settings.width
		&& mouse_y >= menu->button_settings.pos.y
		&& mouse_y <= menu->button_settings.pos.y + menu->button_settings.height)
	{
		menu->button_settings.background_color = BUTTON_HOVER_COLOR;
	}
	else
		menu->button_settings.background_color = BUTTON_COLOR;
}

void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	get_transition_color(cub3d, &menu->background_color);
	draw_start_menu_background(cub3d, menu);
	draw_rectangle(menu->img, &menu->rect_title);
	check_button_hover(cub3d, menu);
	draw_button(menu->img, &menu->button_start);
	draw_button(menu->img, &menu->button_settings);
}
