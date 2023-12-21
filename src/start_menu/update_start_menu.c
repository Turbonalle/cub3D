#include "../incl/cub3d.h"

void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{

	if (hover_image(cub3d, menu->exit.img))
	{
		menu->exit_hover.img->instances[0].enabled = TRUE;
		menu->exit.img->instances[0].enabled = FALSE;
		menu->arrow_exit.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->exit_hover.img->instances[0].enabled = FALSE;
		menu->exit.img->instances[0].enabled = TRUE;
		menu->arrow_exit.img->instances[0].enabled = FALSE;
	}
	if (hover_image(cub3d, menu->start.img))
	{
		menu->start_hover.img->instances[0].enabled = TRUE;
		menu->start.img->instances[0].enabled = FALSE;
		menu->arrow_start.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->start_hover.img->instances[0].enabled = FALSE;
		menu->start.img->instances[0].enabled = TRUE;
		menu->arrow_start.img->instances[0].enabled = FALSE;
	}
	if (hover_image(cub3d, menu->level.img))
	{
		menu->level_hover.img->instances[0].enabled = TRUE;
		menu->level.img->instances[0].enabled = FALSE;
		menu->arrow_level.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->level_hover.img->instances[0].enabled = FALSE;
		menu->level.img->instances[0].enabled = TRUE;
		menu->arrow_level.img->instances[0].enabled = FALSE;
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

