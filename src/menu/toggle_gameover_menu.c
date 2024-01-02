#include "../incl/cub3d.h"

void	disable_gameover_menu(gameover_menu_t *menu)
{
	menu->img->instances[0].enabled = FALSE;
	menu->title_win.img->instances[0].enabled = FALSE;
	menu->title_gameover.img->instances[0].enabled = FALSE;
	menu->back.img->instances[0].enabled = FALSE;
	menu->back_hover.img->instances[0].enabled = FALSE;
	menu->restart.img->instances[0].enabled = FALSE;
	menu->restart_hover.img->instances[0].enabled = FALSE;
	menu->arrow_back.img->instances[0].enabled = FALSE;
	menu->arrow_restart.img->instances[0].enabled = FALSE;
}

void	enable_gameover_menu(gameover_menu_t *menu, int win)
{
	menu->img->instances[0].enabled = TRUE;
	if (win == WIN)
		menu->title_win.img->instances[0].enabled = TRUE;
	else
		menu->title_gameover.img->instances[0].enabled = TRUE;
	menu->back.img->instances[0].enabled = TRUE;
	menu->restart.img->instances[0].enabled = TRUE;
}
