#include "../incl/cub3d.h"

void	set_key_and_letter(int *key, char *letter, char c)
{
	*key = FALSE;
	*letter = c;
}

void	get_letter(cub3d_t *cub3d, name_menu_t *menu)
{
	if (cub3d->keys.a)
		set_key_and_letter(&cub3d->keys.a, &menu->letter, 'a');
	else if (cub3d->keys.b)
		set_key_and_letter(&cub3d->keys.b, &menu->letter, 'b');
	else if (cub3d->keys.c)
		set_key_and_letter(&cub3d->keys.c, &menu->letter, 'c');
	else if (cub3d->keys.d)
		set_key_and_letter(&cub3d->keys.d, &menu->letter, 'd');
	else if (cub3d->keys.e)
		set_key_and_letter(&cub3d->keys.e, &menu->letter, 'e');
	else if (cub3d->keys.f)
		set_key_and_letter(&cub3d->keys.f, &menu->letter, 'f');
	else if (cub3d->keys.g)
		set_key_and_letter(&cub3d->keys.g, &menu->letter, 'g');
	else if (cub3d->keys.h)
		set_key_and_letter(&cub3d->keys.h, &menu->letter, 'h');
	else if (cub3d->keys.i)
		set_key_and_letter(&cub3d->keys.i, &menu->letter, 'i');
	else if (cub3d->keys.j)
		set_key_and_letter(&cub3d->keys.j, &menu->letter, 'j');
	else if (cub3d->keys.k)
		set_key_and_letter(&cub3d->keys.k, &menu->letter, 'k');
	else if (cub3d->keys.l)
		set_key_and_letter(&cub3d->keys.l, &menu->letter, 'l');
	else if (cub3d->keys.m)
		set_key_and_letter(&cub3d->keys.m, &menu->letter, 'm');
	else if (cub3d->keys.n)
		set_key_and_letter(&cub3d->keys.n, &menu->letter, 'n');
	else if (cub3d->keys.o)
		set_key_and_letter(&cub3d->keys.o, &menu->letter, 'o');
	else if (cub3d->keys.p)
		set_key_and_letter(&cub3d->keys.p, &menu->letter, 'p');
	else if (cub3d->keys.q)
		set_key_and_letter(&cub3d->keys.q, &menu->letter, 'q');
	else if (cub3d->keys.r)
		set_key_and_letter(&cub3d->keys.r, &menu->letter, 'r');
	else if (cub3d->keys.s)
		set_key_and_letter(&cub3d->keys.s, &menu->letter, 's');
	else if (cub3d->keys.t)
		set_key_and_letter(&cub3d->keys.t, &menu->letter, 't');
	else if (cub3d->keys.u)
		set_key_and_letter(&cub3d->keys.u, &menu->letter, 'u');
	else if (cub3d->keys.v)
		set_key_and_letter(&cub3d->keys.v, &menu->letter, 'v');
	else if (cub3d->keys.w)
		set_key_and_letter(&cub3d->keys.w, &menu->letter, 'w');
	else if (cub3d->keys.x)
		set_key_and_letter(&cub3d->keys.x, &menu->letter, 'x');
	else if (cub3d->keys.y)
		set_key_and_letter(&cub3d->keys.y, &menu->letter, 'y');
	else if (cub3d->keys.z)
		set_key_and_letter(&cub3d->keys.z, &menu->letter, 'z');
	else if (cub3d->keys.space)
		set_key_and_letter(&cub3d->keys.space, &menu->letter, ' ');
}

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

void	update_letter(cub3d_t *cub3d, name_menu_t *menu)
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

	char *name_copy = ft_strdup(menu->name);
	add_record(&cub3d->level->records, cub3d->time_finished, name_copy, cub3d->leaderboard.n_entries);
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->name[i] = '\0';
}

void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	// int	i;

	if (menu->changed == TRUE)
	{
		if (cub3d->keys.enter || cub3d->keys.escape)
		{
			printf("submitting name\n");
			submit_name(cub3d, menu);
			printf("disabling name menu\n");
			menu->img->instances[0].enabled = FALSE;
			delete_name_menu(menu);
			printf("drawing leaderboard\n");
			draw_leaderboard(cub3d, &cub3d->leaderboard);
			printf("setting state to leaderboard\n");
			cub3d->state = STATE_LEADERBOARD;
			menu->changed = FALSE;
			return ;
		}
		handle_backspace(cub3d, menu);
		get_letter(cub3d, menu);
		update_letter(cub3d, menu);
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