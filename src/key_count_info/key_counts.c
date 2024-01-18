/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_counts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:00:55 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:53:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	draw_door_open(t_cub3d *cub3d, int index)
{
	mlx_delete_image(cub3d->mlx,
		cub3d->level->key_groups[index].img_text_key_count);
	cub3d->level->key_groups[index].img_text_key_count = mlx_put_string(
			cub3d->mlx,
			"open",
			cub3d->level->key_groups[index].key_icon_coords.x
			+ cub3d->mlx->width * 0.03,
			cub3d->level->key_groups[index].key_icon_coords.y
			+ cub3d->mlx->height * 0.01);
}

static char	*get_key_count_text(t_cub3d *cub3d, int index)
{
	char	*text_collected;
	char	*text_collected_slash;
	char	*text_total;
	char	*text;

	nullify_strings(&text_collected, &text_total, &text_collected_slash);
	text_collected = ft_itoa(cub3d->level->key_groups[index].num_keys_total
			- cub3d->level->door_groups[index].num_keys_left);
	if (!text_collected)
		return (NULL);
	text_total = ft_itoa(cub3d->level->key_groups[index].num_keys_total);
	if (!text_total)
	{
		free_non_null_strings(text_collected, text_total, text_collected_slash);
		return (NULL);
	}
	text_collected_slash = ft_strjoin(text_collected, "/");
	if (!text_collected_slash)
	{
		free_non_null_strings(text_collected, text_total, text_collected_slash);
		return (NULL);
	}
	text = ft_strjoin(text_collected_slash, text_total);
	free_non_null_strings(text_collected, text_total, text_collected_slash);
	return (text);
}

static int	draw_key_count(t_cub3d *cub3d, int index)
{
	char	*text;

	text = get_key_count_text(cub3d, index);
	if (!text)
		return (err("MALLOC fail in update_key_count"));
	if (cub3d->level->key_groups[index].img_text_key_count)
		mlx_delete_image(cub3d->mlx,
			cub3d->level->key_groups[index].img_text_key_count);
	cub3d->level->key_groups[index].img_text_key_count = mlx_put_string(
			cub3d->mlx,
			text,
			cub3d->level->key_groups[index].key_icon_coords.x
			+ cub3d->mlx->width * 0.03,
			cub3d->level->key_groups[index].key_icon_coords.y
			+ cub3d->mlx->height * 0.01);
	free(text);
	return (SUCCESS);
}

int	draw_key_counts(t_cub3d *cub3d)
{
	int	index;

	index = 0;
	while (index < NUM_DOORS_MAX)
	{
		if (cub3d->level->key_groups[index].keys)
		{
			if (cub3d->level->door_groups[index].num_keys_left == 0)
				draw_door_open(cub3d, index);
			else
			{
				if (!draw_key_count(cub3d, index))
					return (FAIL);
			}
		}
		index++;
	}
	return (SUCCESS);
}
