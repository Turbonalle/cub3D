#include "../incl/cub3d.h"

void	print_letter_indexes(name_menu_t *menu, int backspace)
{
	int i;

	i = -1;
	while (++i < menu->current)
	{
		if (i == menu->current - 1 && backspace == 0)
			printf(TERMINAL_GREEN);
		else if (i == menu->current - 1 && backspace == 1)
			printf(TERMINAL_RED);
		else
			printf(TERMINAL_RESET);
		if (menu->name[i] == '\0')
			printf("   ");
		else
			printf(" %c ", menu->name[i]);
	}
	printf(TERMINAL_RESET);
	printf("\n");
	i = -1;
	while (++i < menu->current)
	{
		if (i == menu->current - 1 && backspace == 0)
			printf(TERMINAL_GREEN);
		else if (i == menu->current - 1 && backspace == 1)
			printf(TERMINAL_RED);
		else
			printf(TERMINAL_RESET);
		if (menu->letter_index[i] == 0)
			printf("   ");
		else
		{
			if (menu->letter_index[i] < 10)
				printf(" %d ", menu->letter_index[i]);
			else
				printf("%d ", menu->letter_index[i]);
		}
	}
	printf(TERMINAL_RESET);
	printf("\n\n");
}

void	update_letter(mlx_t *mlx, name_menu_t *menu, char letter, int i)
{
	menu->name[menu->current] = letter;
	menu->letter_index[menu->current] = mlx_image_to_window(mlx, menu->letters_img[i], menu->box[menu->current].pos.x + menu->box[menu->current].width * 0.5, menu->box[menu->current].pos.y + menu->box[menu->current].height * 0.5);
	menu->letters_img[i]->instances[menu->letter_index[menu->current]].x -= menu->letters_img[i]->width * 0.5;
	menu->letters_img[i]->instances[menu->letter_index[menu->current]].y -= menu->letters_img[i]->height * 0.5;
	if (menu->current < MAX_NAME_LENGTH)
		menu->current++;
	print_letter_indexes(menu, 0);
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
			menu->current--;
			int letter = menu->name[menu->current] - 'a';
			int index = menu->letter_index[menu->current];
			menu->name[menu->current] = '\0';
			menu->letters_img[letter]->instances[index].enabled = FALSE;
			print_letter_indexes(menu, 1);
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