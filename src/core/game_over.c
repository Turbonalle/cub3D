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
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
	mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
	free_level(cub3d);
	if (cub3d->level != &cub3d->levels[0] && is_top_score(cub3d->level, cub3d->time_finished))
	{
		enable_name_menu(&cub3d->name_menu);
		cub3d->state = STATE_ENTERNAME;
		handle_cursor(cub3d);
	}
	else if (cub3d->speedrun)
	{
		enable_level_menu(&cub3d->level_menu);
		cub3d->speedrun = FALSE;
		cub3d->state = STATE_LEVEL;
		handle_cursor(cub3d);
	}
	else
	{
		enable_start_menu(&cub3d->start_menu);
		cub3d->speedrun = FALSE;
		cub3d->state = STATE_START;
		handle_cursor(cub3d);
	}
}
