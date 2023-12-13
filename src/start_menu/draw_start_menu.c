#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void	disable_start_menu(start_menu_t *menu)
{
	menu->img->instances[0].enabled = FALSE;
	menu->text_title->instances[0].enabled = FALSE;
	menu->text_start->instances[0].enabled = FALSE;
	menu->text_level->instances[0].enabled = FALSE;
	menu->text_settings->instances[0].enabled = FALSE;
	menu->text_exit->instances[0].enabled = FALSE;
}

void	enable_start_menu(start_menu_t *menu)
{
	menu->img->instances[0].enabled = TRUE;
	menu->text_title->instances[0].enabled = TRUE;
	menu->text_start->instances[0].enabled = TRUE;
	menu->text_level->instances[0].enabled = TRUE;
	menu->text_settings->instances[0].enabled = TRUE;
	menu->text_exit->instances[0].enabled = TRUE;
}
