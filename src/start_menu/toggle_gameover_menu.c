#include "../incl/cub3d.h"

void	disable_gameover_menu(gameover_menu_t *menu)
{
	menu->img->instances[0].enabled = FALSE;
	menu->text_gameover->instances[0].enabled = FALSE;
	menu->button_exit.text->instances[0].enabled = FALSE;
	menu->button_restart.text->instances[0].enabled = FALSE;
}

void	enable_gameover_menu(gameover_menu_t *menu)
{
	menu->img->instances[0].enabled = TRUE;
	menu->text_gameover->instances[0].enabled = TRUE;
	menu->button_exit.text->instances[0].enabled = TRUE;
	menu->button_restart.text->instances[0].enabled = TRUE;
	menu->button_exit.state = FALSE;
	menu->button_restart.state = FALSE;
}
