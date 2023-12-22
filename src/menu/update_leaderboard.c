#include "../incl/cub3d.h"

void	update_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int i;
	get_transition_color(cub3d, &board->background_color);
	draw_menu_background(board->img, board->background_color);
	draw_rectangle(board->img, &board->rect_title);

	i = -1;
	while (++i < cub3d->n_levels)
		draw_rectangle(board->img, &board->rect_level[i]);
	if (hover_button(cub3d, &board->button_back))
		board->button_back.background_color = BUTTON_HOVER_COLOR;
	else
		board->button_back.background_color = BUTTON_COLOR;
	draw_button(board->img, &board->button_back);
}