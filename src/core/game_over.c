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
	printf("Game over\n");
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	printf("Time finished = %d\n", cub3d->time_finished);
	if (cub3d->level != &cub3d->levels[0] && is_top_score(cub3d->level, cub3d->time_finished))
	{
		printf("Top score\n");
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		draw_name_menu(cub3d, &cub3d->name_menu);
		cub3d->state = STATE_ENTERNAME;
	}
	else
	{
		printf("Not top score\n");
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		draw_start_menu(cub3d, &cub3d->start_menu);
		cub3d->state = STATE_START;
		// cub3d->state = STATE_GAMEOVER;
	}
}