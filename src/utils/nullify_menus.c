#include "../incl/cub3d.h"

void	nullify_start_menu(start_menu_t *menu)
{
	menu->img = NULL;
	nullify_png(&menu->title);
	nullify_png(&menu->exit);
	nullify_png(&menu->start);
	nullify_png(&menu->level);
	nullify_png(&menu->exit_hover);
	nullify_png(&menu->start_hover);
	nullify_png(&menu->level_hover);
	nullify_png(&menu->arrow_exit);
	nullify_png(&menu->arrow_start);
	nullify_png(&menu->arrow_level);
}

void	nullify_leaderboard(leaderboard_t *leaderboard)
{
	int	i;

	leaderboard->img = NULL;
	nullify_png(&leaderboard->title);
	nullify_png(&leaderboard->back);
	nullify_png(&leaderboard->back_hover);
	i = -1;
	while (++i < LEVELS)
		leaderboard->text_level[i] = NULL;
}

void	nullify_gameover_menu(gameover_menu_t *menu)
{
	menu->img = NULL;
	nullify_png(&menu->title_win);
	nullify_png(&menu->title_gameover);
	nullify_png(&menu->back);
	nullify_png(&menu->back_hover);
	nullify_png(&menu->restart);
	nullify_png(&menu->restart_hover);
	nullify_png(&menu->arrow_back);
	nullify_png(&menu->arrow_restart);
	nullify_png(&menu->timer);
	menu->text_time = NULL;
}

void	nullify_name_menu(name_menu_t *menu)
{
	int	i;

	menu->img = NULL;
	nullify_png(&menu->title_win);
	nullify_png(&menu->title_top3);
	nullify_png(&menu->back);
	nullify_png(&menu->back_hover);
	nullify_png(&menu->timer);
	menu->text_time = NULL;
	i = -1;
	while (++i < ALPHABET_LENGTH)
		menu->letters_img[i] = NULL;
}

void	nullify_pause_menu(pause_menu_t *menu)
{
	menu->bg = NULL;
	menu->menu = NULL;
	nullify_png(&menu->title);
	menu->text_title = NULL;
	menu->text_fps = NULL;
	menu->text_fisheye = NULL;
	menu->text_mouse = NULL;
	menu->text_mouse_sensitivity = NULL;
	menu->box_fps[0].text = NULL;
	menu->box_fps[1].text = NULL;
	menu->box_fps[2].text = NULL;
	menu->box_fps[3].text = NULL;
	menu->box_fisheye[0].text = NULL;
	menu->box_fisheye[1].text = NULL;
	menu->box_mouse[0].text = NULL;
	menu->box_mouse[1].text = NULL;
	menu->sensitivity_slider.marker = NULL;
}