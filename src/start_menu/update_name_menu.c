#include "../incl/cub3d.h"

void	handle_backspace(cub3d_t *cub3d, name_menu_t *menu)
{
	if (cub3d->keys.backspace)
	{
		if (menu->current > 0)
		{
			menu->box[menu->current].letter[0] = '\0';
			menu->box[menu->current].letter[1] = '\0';
			menu->current--;
		}
	}
}

void	update_char(cub3d_t *cub3d, name_menu_t *menu)
{
	if (cub3d->keys.shift)
		menu->letter = ft_toupper(menu->letter);
	menu->box[menu->current].letter[0] = menu->letter;
	if (menu->current < MAX_NAME_LENGTH - 1)
		menu->current++;
}

void	submit_name(cub3d_t *cub3d, name_menu_t *menu)
{
	int		i;

	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->name[i] = menu->box[i].letter[0];
	add_record(&cub3d->level->records, cub3d->time_finished, menu->name, cub3d->leaderboard.n_entries);
}

void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	// int	i;

	if (menu->changed == TRUE)
	{
		if (cub3d->keys.escape)
		{
			printf("ESC: Deleting name menu\n");
			delete_name_menu(cub3d, menu);
			draw_start_menu(cub3d, &cub3d->start_menu);
			printf("Setting state to start\n");
			cub3d->state = STATE_START;
			return ;
		}
		if (cub3d->keys.enter)
		{
			submit_name(cub3d, menu);
			delete_name_menu(cub3d, menu);
			draw_leaderboard(cub3d, &cub3d->leaderboard);
			cub3d->state = STATE_LEADERBOARD;
			return ;
		}
		// handle_backspace(cub3d, menu);
		// update_char(cub3d, menu);
		// i = -1;
		// while (++i < MAX_NAME_LENGTH)
		// 	mlx_delete_image(cub3d->mlx, menu->box[i].img);
		// i = -1;
		// while (++i < MAX_NAME_LENGTH)
		// {
		// 	mlx_put_string(cub3d->mlx, menu->box[i].letter, menu->box[i].pos.x + menu->box[i].width * 0.5, menu->box[i].pos.y + menu->box[i].height * 0.5);
		// 	center(menu->box[i].img);
		// }
		menu->changed = FALSE;
	}
}