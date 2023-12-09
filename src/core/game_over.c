#include "../incl/cub3d.h"

int	top_score(level_t *level, int time)
{
	record_t	*ptr;

	ptr = level->records;
	while (ptr)
	{
		if (time < ptr->time)
			return (SUCCESS);
		ptr = ptr->next;
	}
	return (FAIL);
}

void	game_over(cub3d_t *cub3d)
{
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	if (top_score(cub3d->level, cub3d->time_finished))
	{
		draw_name_menu(cub3d, &cub3d->name_menu);
		cub3d->state = STATE_ENTERNAME;
	}
	else
	{
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		draw_start_menu(cub3d, &cub3d->start_menu);
		cub3d->state = STATE_GAMEOVER;
	}
}