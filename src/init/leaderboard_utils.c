/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaderboard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:42:44 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:26 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_times(mlx_t *mlx, t_record **records,
	t_leaderboard *board, int level)
{
	t_record	*ptr;
	t_vector	pos;
	int			i;
	int			margin_x;
	int			margin_y;

	ptr = *records;
	margin_x = board->rect_level[level - 1].width * 0.1;
	margin_y = board->rect_level[level - 1].height * 0.1;
	pos.x = board->rect_level[level - 1].pos.x + margin_x;
	i = -1;
	while (++i < board->n_entries && ptr)
	{
		pos.y = board->rect_level[level - 1].pos.y + margin_y + i
			* (board->rect_level[level - 1].height - 2 * margin_y)
			/ board->n_entries;
		ptr->text_time = mlx_put_string(mlx, ptr->time_str, pos.x, pos.y);
		ptr = ptr->next;
	}
}

void	draw_names(mlx_t *mlx, t_record **records,
	t_leaderboard *board, int level)
{
	t_record	*ptr;
	t_vector	pos;
	int			i;
	int			margin_x;
	int			margin_y;

	ptr = *records;
	margin_x = board->rect_level[level - 1].width * 0.1;
	margin_y = board->rect_level[level - 1].height * 0.1;
	pos.x = board->rect_level[level - 1].pos.x + margin_x;
	i = -1;
	while (++i < board->n_entries && ptr)
	{
		pos.y = board->rect_level[level - 1].pos.y + margin_y + i
			* (board->rect_level[level - 1].height - 2 * margin_y)
			/ board->n_entries + margin_y;
		ptr->text_name = mlx_put_string(mlx, ptr->name, pos.x, pos.y);
		ptr = ptr->next;
	}
}

void	set_record_texts(t_cub3d *cub3d, t_leaderboard *board)
{
	int	i;

	i = 0;
	while (++i <= cub3d->n_levels)
	{
		draw_names(cub3d->mlx, &cub3d->levels[i].records, board, i);
		draw_times(cub3d->mlx, &cub3d->levels[i].records, board, i);
	}
}

int	load_png_board(t_leaderboard *board)
{
	board->title.texture = mlx_load_png(LEADERBOARD_TITLE_PNG);
	if (!board->title.texture)
		return (0);
	board->back.texture = mlx_load_png(BACK_PNG);
	if (!board->back.texture)
	{
		mlx_delete_texture(board->title.texture);
		return (0);
	}
	board->back_hover.texture = mlx_load_png(BACK_HOVER_PNG);
	if (!board->back_hover.texture)
	{
		mlx_delete_texture(board->title.texture);
		mlx_delete_texture(board->back.texture);
		return (0);
	}
	return (1);
}

int	init_images_board(mlx_t *mlx, t_leaderboard *board)
{
	board->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!board->img)
		return (err("Failed to create leaderboard image"));
	board->title.img = mlx_texture_to_image(mlx, board->title.texture);
	if (!board->title.img)
		return (err("Failed to create leaderboard title image"));
	board->back.img = mlx_texture_to_image(mlx, board->back.texture);
	if (!board->back.img)
		return (err("Failed to create leaderboard back image"));
	board->back_hover.img
		= mlx_texture_to_image(mlx, board->back_hover.texture);
	if (!board->back_hover.img)
		return (err("Failed to create leaderboard back hover image"));
	return (SUCCESS);
}
