#include "../incl/cub3d.h"

int	update_letter(mlx_t *mlx, name_menu_t *menu, int *key, int i)
{
	*key = FALSE;
	menu->name[menu->current] = i + 'a';
	menu->letter_index[menu->current] = mlx_image_to_window(mlx, menu->letters_img[i], menu->box[menu->current].pos.x + menu->box[menu->current].width * 0.5, menu->box[menu->current].pos.y + menu->box[menu->current].height * 0.5);
	menu->letters_img[i]->instances[menu->letter_index[menu->current]].x -= menu->letters_img[i]->width * 0.5;
	menu->letters_img[i]->instances[menu->letter_index[menu->current]].y -= menu->letters_img[i]->height * 0.5;
	if (menu->current < MAX_NAME_LENGTH)
		menu->current++;
	print_letter_indexes(menu, 0);
	return (1);
}

void	get_letter(cub3d_t *cub3d, name_menu_t *menu)
{
	if (get_letter_first_third(cub3d, menu))
		return ;
	else if (get_letter_second_third(cub3d, menu))
		return ;
	else
		get_letter_last_third(cub3d, menu);
}

int	name_is_empty(name_menu_t *menu)
{
	return (menu->name[0] == '\0');
}

void	submit_name(cub3d_t *cub3d, name_menu_t *menu)
{
	remove_record_image_pointers(cub3d);
	if (name_is_empty(menu))
		add_record(cub3d, &cub3d->level->records, cub3d->time_finished, ft_strdup("Anonymous"), cub3d->leaderboard.n_entries);
	else
		add_record(cub3d, &cub3d->level->records, cub3d->time_finished, ft_strdup(menu->name), cub3d->leaderboard.n_entries);
	int i = get_current_level(cub3d);
	draw_names(cub3d->mlx, &cub3d->level->records, &cub3d->leaderboard, i);
	draw_times(cub3d->mlx, &cub3d->level->records, &cub3d->leaderboard, i);
}

void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		menu->back.img->instances[0].enabled = FALSE;
		menu->back_hover.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->back.img->instances[0].enabled = TRUE;
		menu->back_hover.img->instances[0].enabled = FALSE;
	}
	if (menu->changed == TRUE)
	{
		if (cub3d->keys.escape)
		{
			disable_name_menu(cub3d->mlx, menu);
			enable_level_menu(&cub3d->level_menu);
			cub3d->state = STATE_LEVEL;
			cub3d->speedrun = FALSE;
			menu->changed = FALSE;
			return ;
		}
		if (cub3d->keys.enter)
		{
			submit_name(cub3d, menu);
			disable_name_menu(cub3d->mlx, menu);
			enable_leaderboard(cub3d, &cub3d->leaderboard);
			cub3d->state = STATE_LEADERBOARD;
			cub3d->speedrun = FALSE;
			menu->changed = FALSE;
			return ;
		}
		if (cub3d->keys.backspace)
			handle_backspace(cub3d, menu);
		else if (menu->current < MAX_NAME_LENGTH)
			get_letter(cub3d, menu);
		menu->changed = FALSE;
	}
}
