#include "../incl/cub3d.h"

void	update_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu)
{
	if (hover_button(cub3d, &menu->button_exit))
		menu->button_exit.background_color = BUTTON_HOVER_COLOR;
	else
		menu->button_exit.background_color = BUTTON_COLOR;
	if (hover_button(cub3d, &menu->button_restart))
		menu->button_restart.background_color = BUTTON_HOVER_COLOR;
	else
		menu->button_restart.background_color = BUTTON_COLOR;
	draw_button(menu->img, &menu->button_exit);
	draw_button(menu->img, &menu->button_restart);
}