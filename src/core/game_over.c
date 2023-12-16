#include "../incl/cub3d.h"

int	is_top_score(level_t *level, int time)
{
	record_t	*ptr;
	int			i;

	i = -1;
	ptr = level->records;
	while (++i < N_ENTRIES)
	{
		if (ptr == NULL)
			return (TRUE);
		if (time < ptr->time)
			return (TRUE);
		ptr = ptr->next;
	}
	return (FALSE);
}

void	game_over(cub3d_t *cub3d)
{
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	if (cub3d->level != &cub3d->levels[0] && is_top_score(cub3d->level, cub3d->time_finished))
	{
		draw_name_menu(cub3d, &cub3d->name_menu);
		cub3d->state = STATE_ENTERNAME;
	}
	else
	{
		draw_start_menu(cub3d, &cub3d->start_menu);
		cub3d->state = STATE_START;
		// cub3d->state = STATE_GAMEOVER;
	}
}