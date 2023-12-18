#include "../incl/cub3d.h"

void	update_letter(mlx_t *mlx, name_menu_t *menu, int *key, int i)
{
	*key = FALSE;
	menu->name[menu->current] = i + 'a';
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
		update_letter(cub3d->mlx, menu, &cub3d->keys.a, a);
	else if (cub3d->keys.b)
		update_letter(cub3d->mlx, menu, &cub3d->keys.b, b);
	else if (cub3d->keys.c)
		update_letter(cub3d->mlx, menu, &cub3d->keys.c, c);
	else if (cub3d->keys.d)
		update_letter(cub3d->mlx, menu, &cub3d->keys.d, d);
	else if (cub3d->keys.e)
		update_letter(cub3d->mlx, menu, &cub3d->keys.e, e);
	else if (cub3d->keys.f)
		update_letter(cub3d->mlx, menu, &cub3d->keys.f, f);
	else if (cub3d->keys.g)
		update_letter(cub3d->mlx, menu, &cub3d->keys.g, g);
	else if (cub3d->keys.h)
		update_letter(cub3d->mlx, menu, &cub3d->keys.h, h);
	else if (cub3d->keys.i)
		update_letter(cub3d->mlx, menu, &cub3d->keys.i, i);
	else if (cub3d->keys.j)
		update_letter(cub3d->mlx, menu, &cub3d->keys.j, j);
	else if (cub3d->keys.k)
		update_letter(cub3d->mlx, menu, &cub3d->keys.k, k);
	else if (cub3d->keys.l)
		update_letter(cub3d->mlx, menu, &cub3d->keys.l, l);
	else if (cub3d->keys.m)
		update_letter(cub3d->mlx, menu, &cub3d->keys.m, m);
	else if (cub3d->keys.n)
		update_letter(cub3d->mlx, menu, &cub3d->keys.n, n);
	else if (cub3d->keys.o)
		update_letter(cub3d->mlx, menu, &cub3d->keys.o, o);
	else if (cub3d->keys.p)
		update_letter(cub3d->mlx, menu, &cub3d->keys.p, p);
	else if (cub3d->keys.q)
		update_letter(cub3d->mlx, menu, &cub3d->keys.q, q);
	else if (cub3d->keys.r)
		update_letter(cub3d->mlx, menu, &cub3d->keys.r, r);
	else if (cub3d->keys.s)
		update_letter(cub3d->mlx, menu, &cub3d->keys.s, s);
	else if (cub3d->keys.t)
		update_letter(cub3d->mlx, menu, &cub3d->keys.t, t);
	else if (cub3d->keys.u)
		update_letter(cub3d->mlx, menu, &cub3d->keys.u, u);
	else if (cub3d->keys.v)
		update_letter(cub3d->mlx, menu, &cub3d->keys.v, v);
	else if (cub3d->keys.w)
		update_letter(cub3d->mlx, menu, &cub3d->keys.w, w);
	else if (cub3d->keys.x)
		update_letter(cub3d->mlx, menu, &cub3d->keys.x, x);
	else if (cub3d->keys.y)
		update_letter(cub3d->mlx, menu, &cub3d->keys.y, y);
	else if (cub3d->keys.z)
		update_letter(cub3d->mlx, menu, &cub3d->keys.z, z);
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

int	name_is_empty(name_menu_t *menu)
{
	return (menu->name[0] == '\0');
}

void	remove_record_image_pointers(cub3d_t *cub3d)
{
	record_t	*ptr;

	ptr = cub3d->level->records;
	while (ptr)
	{
		mlx_delete_image(cub3d->mlx, ptr->text_name);
		mlx_delete_image(cub3d->mlx, ptr->text_time);
		ptr = ptr->next;
	}

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
	if (menu->changed == TRUE)
	{
		if (cub3d->keys.escape)
		{
			disable_name_menu(menu);
			enable_leaderboard(cub3d, &cub3d->leaderboard);
			cub3d->state = STATE_LEADERBOARD;
			menu->changed = FALSE;
			return ;
		}
		if (cub3d->keys.enter)
		{
			submit_name(cub3d, menu);
			disable_name_menu(menu);
			enable_leaderboard(cub3d, &cub3d->leaderboard);
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