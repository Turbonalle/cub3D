
#include "../incl/cub3d.h"

void	disable_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	record_t	*ptr;
	int			i;

	board->img->instances[0].enabled = FALSE;
	board->title.img->instances[0].enabled = FALSE;
	board->back.img->instances[0].enabled = FALSE;
	board->back_hover.img->instances[0].enabled = FALSE;
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		ptr = cub3d->levels[i].records;
		int entry = -1;
		while (++entry < board->n_entries && ptr)
		{
			ptr->text_time->instances[0].enabled = FALSE;
			ptr->text_name->instances[0].enabled = FALSE;
			ptr = ptr->next;
		}
	}
}

void	enable_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	record_t	*ptr;
	int			i;

	board->img->instances[0].enabled = TRUE;
	board->title.img->instances[0].enabled = TRUE;
	board->back.img->instances[0].enabled = TRUE;
	board->back_hover.img->instances[0].enabled = TRUE;
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		ptr = cub3d->levels[i].records;
		int entry = -1;
		while (++entry < board->n_entries && ptr)
		{
			ptr->text_time->instances[0].enabled = TRUE;
			ptr->text_name->instances[0].enabled = TRUE;
			ptr = ptr->next;
		}
	}
}
