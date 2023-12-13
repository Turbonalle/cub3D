#include "../incl/cub3d.h"

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
	else if (cub3d->keys.c)
		update_letter(cub3d->mlx, menu, 'c', c);
	else if (cub3d->keys.d)
		update_letter(cub3d->mlx, menu, 'd', d);
	else if (cub3d->keys.e)
		update_letter(cub3d->mlx, menu, 'e', e);
	else if (cub3d->keys.f)
		update_letter(cub3d->mlx, menu, 'f', f);
	else if (cub3d->keys.g)
		update_letter(cub3d->mlx, menu, 'g', g);
	else if (cub3d->keys.h)
		update_letter(cub3d->mlx, menu, 'h', h);
	else if (cub3d->keys.i)
		update_letter(cub3d->mlx, menu, 'i', i);
	else if (cub3d->keys.j)
		update_letter(cub3d->mlx, menu, 'j', j);
	else if (cub3d->keys.k)
		update_letter(cub3d->mlx, menu, 'k', k);
	else if (cub3d->keys.l)
		update_letter(cub3d->mlx, menu, 'l', l);
	else if (cub3d->keys.m)
		update_letter(cub3d->mlx, menu, 'm', m);
	else if (cub3d->keys.n)
		update_letter(cub3d->mlx, menu, 'n', n);
	else if (cub3d->keys.o)
		update_letter(cub3d->mlx, menu, 'o', o);
	else if (cub3d->keys.p)
		update_letter(cub3d->mlx, menu, 'p', p);
	else if (cub3d->keys.q)
		update_letter(cub3d->mlx, menu, 'q', q);
	else if (cub3d->keys.r)
		update_letter(cub3d->mlx, menu, 'r', r);
	else if (cub3d->keys.s)
		update_letter(cub3d->mlx, menu, 's', s);
	else if (cub3d->keys.t)
		update_letter(cub3d->mlx, menu, 't', t);
	else if (cub3d->keys.u)
		update_letter(cub3d->mlx, menu, 'u', u);
	else if (cub3d->keys.v)
		update_letter(cub3d->mlx, menu, 'v', v);
	else if (cub3d->keys.w)
		update_letter(cub3d->mlx, menu, 'w', w);
	else if (cub3d->keys.x)
		update_letter(cub3d->mlx, menu, 'x', x);
	else if (cub3d->keys.y)
		update_letter(cub3d->mlx, menu, 'y', y);
	else if (cub3d->keys.z)
		update_letter(cub3d->mlx, menu, 'z', z);
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
	add_record(&cub3d->level->records, cub3d->time_finished, ft_strdup(menu->name), cub3d->leaderboard.n_entries);
}

void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	if (menu->changed == TRUE)
	{
		if (cub3d->keys.enter || cub3d->keys.escape)
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