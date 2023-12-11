#include "../incl/cub3d.h"

int	is_top_score(level_t *level, int time)
{
	record_t	*ptr;
	int			i;

	printf("Checking if %d is a top score\n", time);
	i = -1;
	ptr = level->records;
	while (++i < N_ENTRIES)
	{
		if (ptr == NULL)
		{
			printf("Leaderboard is not full\n");
			return (TRUE);
		}
		printf("Comparing %d to %d\n", time, ptr->time);
		if (time < ptr->time)
			return (TRUE);
		ptr = ptr->next;
	}
	return (FALSE);
}

void	game_over(cub3d_t *cub3d)
{
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	printf("Time: %d\n", cub3d->time_finished);
	if (cub3d->level != &cub3d->levels[0] && is_top_score(cub3d->level, cub3d->time_finished))
	{
		printf("New top score!\n");
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		printf("Drawing name menu\n");
		draw_name_menu(cub3d, &cub3d->name_menu);
		printf("Setting state to enter name\n");
		// while (cub3d->keys.w || cub3d->keys.a || cub3d->keys.s || cub3d->keys.d)
		// 	;
		cub3d->state = STATE_ENTERNAME;
	}
	else
	{
		printf("No top score...\n");
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		draw_start_menu(cub3d, &cub3d->start_menu);
		cub3d->state = STATE_GAMEOVER;
	}
}