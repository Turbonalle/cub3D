#include "../incl/cub3d.h"

void	update_letter(mlx_t *mlx, name_menu_t *menu, char letter, int n)
{
		menu->name[menu->current] = letter;
		menu->n_letters[n] = mlx_image_to_window(mlx, menu->letters_img[n], menu->box[menu->current].pos.x + menu->box[menu->current].width * 0.5, menu->box[menu->current].pos.y + menu->box[menu->current].height * 0.5);
		menu->letters_img[n]->instances[menu->n_letters[n]].x -= menu->letters_img[n]->width * 0.5;
		menu->letters_img[n]->instances[menu->n_letters[n]].y -= menu->letters_img[n]->height * 0.5;
		if (menu->current < MAX_NAME_LENGTH)
			menu->current++;
}

void	get_letter(cub3d_t *cub3d, name_menu_t *menu)
{
	if (cub3d->keys.a)
		update_letter(cub3d->mlx, menu, 'a', a);
	else if (cub3d->keys.b)
		update_letter(cub3d->mlx, menu, 'b', b);
}

void	handle_backspace(cub3d_t *cub3d, name_menu_t *menu)
{
	if (cub3d->keys.backspace)
	{
		if (menu->current > 0)
		{
			int letter = menu->name[menu->current - 1] - 'a';
			int index = menu->n_letters[letter];
			menu->name[menu->current - 1] = '\0';
			menu->letters_img[letter]->instances[index].enabled = FALSE;
			menu->n_letters[letter]--;
			menu->current--;
		}
	}
}

void	submit_name(cub3d_t *cub3d, name_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->name[i] = menu->box[i].letter[0];

	add_record(&cub3d->level->records, cub3d->time_finished, ft_strdup(menu->name), cub3d->leaderboard.n_entries);
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->name[i] = '\0';
}

void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	if (menu->changed == TRUE)
	{
		if (cub3d->keys.enter || cub3d->keys.escape)
		{
			submit_name(cub3d, menu);
			menu->img->instances[0].enabled = FALSE;
			delete_name_menu(menu);
			draw_leaderboard(cub3d, &cub3d->leaderboard);
			cub3d->state = STATE_LEADERBOARD;
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