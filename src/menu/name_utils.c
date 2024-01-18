/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:47:59 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_letter_first_third(t_cub3d *cub3d, t_name_menu *menu)
{
	if (cub3d->keys.a)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.a, a));
	else if (cub3d->keys.b)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.b, b));
	else if (cub3d->keys.c)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.c, c));
	else if (cub3d->keys.d)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.d, d));
	else if (cub3d->keys.e)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.e, e));
	else if (cub3d->keys.f)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.f, f));
	else if (cub3d->keys.g)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.g, g));
	else if (cub3d->keys.h)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.h, h));
	else if (cub3d->keys.i)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.i, i));
	else if (cub3d->keys.j)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.j, j));
	else if (cub3d->keys.k)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.k, k));
	else
		return (FAIL);
}

int	get_letter_second_third(t_cub3d *cub3d, t_name_menu *menu)
{
	if (cub3d->keys.l)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.l, l));
	else if (cub3d->keys.m)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.m, m));
	else if (cub3d->keys.n)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.n, n));
	else if (cub3d->keys.o)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.o, o));
	else if (cub3d->keys.p)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.p, p));
	else if (cub3d->keys.q)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.q, q));
	else if (cub3d->keys.r)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.r, r));
	else if (cub3d->keys.s)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.s, s));
	else if (cub3d->keys.t)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.t, t));
	else
		return (FAIL);
}

int	get_letter_last_third(t_cub3d *cub3d, t_name_menu *menu)
{
	if (cub3d->keys.u)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.u, u));
	else if (cub3d->keys.v)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.v, v));
	else if (cub3d->keys.w)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.w, w));
	else if (cub3d->keys.x)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.x, x));
	else if (cub3d->keys.y)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.y, y));
	else if (cub3d->keys.z)
		return (update_letter(cub3d->mlx, menu, &cub3d->keys.z, z));
	else
		return (FAIL);
}

void	handle_backspace(t_cub3d *cub3d, t_name_menu *menu)
{
	int	letter;
	int	index;

	if (cub3d->keys.backspace)
	{
		if (menu->current > 0)
		{
			menu->current--;
			letter = menu->name[menu->current] - 'a';
			index = menu->letter_index[menu->current];
			menu->name[menu->current] = '\0';
			menu->letters_img[letter]->instances[index].enabled = FALSE;
			print_letter_indexes(menu, 1);
		}
	}
}

void	remove_record_image_pointers(t_cub3d *cub3d)
{
	t_record	*ptr;

	ptr = cub3d->level->records;
	while (ptr)
	{
		mlx_delete_image(cub3d->mlx, ptr->text_name);
		mlx_delete_image(cub3d->mlx, ptr->text_time);
		ptr = ptr->next;
	}
}
