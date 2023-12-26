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

void	clean_level_data(cub3d_t *cub3d)
{
	cub3d->halo.img->instances[0].enabled = FALSE;
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
	mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
	free_level(cub3d);
}

void	level_finished(cub3d_t *cub3d)
{
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	clean_level_data(cub3d);
	printf("Level finished, all freed\n");
	if (cub3d->level != &cub3d->levels[0]
		&& is_top_score(cub3d->level, cub3d->time_finished))
	{
		enable_name_menu(&cub3d->name_menu);
		cub3d->state = STATE_ENTERNAME;
	}
	else if (cub3d->speedrun)
	{
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
	}
	else
	{
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
	handle_cursor(cub3d);
	cub3d->speedrun = FALSE;
}

void	game_over(cub3d_t *cub3d)
{
	clean_level_data(cub3d);
	enable_gameover_menu(&cub3d->gameover_menu);
	cub3d->state = STATE_GAMEOVER;
	handle_cursor(cub3d);
}
