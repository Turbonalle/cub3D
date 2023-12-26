#include "../incl/cub3d.h"

void	disable_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	record_t	*ptr;
	int			i;

	// printf("disable: board->img\n");
	board->img->instances[0].enabled = FALSE;
	// printf("disable: board->text_title\n");
	board->text_title->instances[0].enabled = FALSE;
	// board->text_back->instances[0].enabled = FALSE;
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		// printf("level %d/%d\n", i, cub3d->n_levels);
		ptr = cub3d->levels[i].records;
		int entry = -1;
		while (++entry < board->n_entries && ptr)
		{
			// printf("entry = %d\n", entry);
			// printf("disable: ptr->text_time\n");
			ptr->text_time->instances[0].enabled = FALSE;
			// printf("disable: ptr->text_name\n");
			ptr->text_name->instances[0].enabled = FALSE;
			ptr = ptr->next;
		}
	}
}

void	enable_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	record_t	*ptr;
	int			i;

	// printf("enable: board->img\n");
	board->img->instances[0].enabled = TRUE;
	// printf("enable: board->text_title\n");
	board->text_title->instances[0].enabled = TRUE;
	// board->text_back->instances[0].enabled = TRUE;
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		// printf("level %d/%d\n", i, cub3d->n_levels);
		ptr = cub3d->levels[i].records;
		int entry = -1;
		while (++entry < board->n_entries && ptr)
		{
			// printf("entry = %d\n", entry);
			// printf("name = %s, time = %d\n", ptr->name, ptr->time);
			// printf("enable: ptr->text_time\n");
			ptr->text_time->instances[0].enabled = TRUE;
			// printf("enable: ptr->text_name\n");
			ptr->text_name->instances[0].enabled = TRUE;
			// printf("next ptr\n");
			ptr = ptr->next;
			// printf("done\n");
		}
	}
}
