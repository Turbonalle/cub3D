#include "../incl/cub3d.h"

void	disable_level_menu(level_menu_t *menu)
{
	menu->img->instances[0].enabled = FALSE;
	menu->text_title->instances[0].enabled = FALSE;
	menu->text_level_1->instances[0].enabled = FALSE;
	menu->text_level_2->instances[0].enabled = FALSE;
	menu->text_level_3->instances[0].enabled = FALSE;
	menu->text_level_4->instances[0].enabled = FALSE;
	menu->text_level_5->instances[0].enabled = FALSE;
	menu->text_level_6->instances[0].enabled = FALSE;
	menu->text_level_7->instances[0].enabled = FALSE;
	menu->text_level_8->instances[0].enabled = FALSE;
	menu->text_back->instances[0].enabled = FALSE;
	menu->text_leaderboard->instances[0].enabled = FALSE;
}

void	enable_level_menu(level_menu_t *menu)
{
	menu->img->instances[0].enabled = TRUE;
	menu->text_title->instances[0].enabled = TRUE;
	menu->text_level_1->instances[0].enabled = TRUE;
	menu->text_level_2->instances[0].enabled = TRUE;
	menu->text_level_3->instances[0].enabled = TRUE;
	menu->text_level_4->instances[0].enabled = TRUE;
	menu->text_level_5->instances[0].enabled = TRUE;
	menu->text_level_6->instances[0].enabled = TRUE;
	menu->text_level_7->instances[0].enabled = TRUE;
	menu->text_level_8->instances[0].enabled = TRUE;
	menu->text_back->instances[0].enabled = TRUE;
	menu->text_leaderboard->instances[0].enabled = TRUE;
}