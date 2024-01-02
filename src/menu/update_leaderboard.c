#include "../incl/cub3d.h"

void	update_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	if (hover_image(cub3d, board->back.img))
	{
		board->back_hover.img->instances[0].enabled = TRUE;
		board->back.img->instances[0].enabled = FALSE;
	}
	else
	{
		board->back_hover.img->instances[0].enabled = FALSE;
		board->back.img->instances[0].enabled = TRUE;
	}
}