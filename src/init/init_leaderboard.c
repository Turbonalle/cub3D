/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_leaderboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:41:41 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:51:41 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_positions_rest(mlx_t *mlx, leaderboard_t *board, vector_t coord)
{
	int			i;
	int			size;
	int			gap;
	int			margin_x;

	size = min(mlx->width * 0.15, mlx->height * 0.25);
	gap = min(board->img->width * 0.05, board->img->height * 0.05);
	margin_x = (board->img->width - (coord.x * size + (coord.x - 1) * gap)) / 2;
	i = -1;
	while (++i < LEVELS)
	{
		board->rect_level[i].color = LEADERBOARD_LEVEL_BACKGROUND_COLOR;
		board->rect_level[i].width = size;
		board->rect_level[i].height = size;
		board->rect_level[i].pos.x = margin_x + (i % coord.x) * (size + gap);
		board->rect_level[i].pos.y = board->img->height * 0.32
			+ (i / coord.x) * (size + gap);
	}
}

static void	set_positions(mlx_t *mlx, leaderboard_t *board)
{
	int			size;
	int			gap;
	int			margin_x;
	vector_t	coord;

	board->title.pos.x = (board->img->width - board->title.img->width) / 2;
	board->title.pos.y = board->img->height * 0.12;
	size = min(mlx->width * 0.15, mlx->height * 0.25);
	coord.y = 2;
	if (LEVELS % coord.y == 0)
		coord.x = LEVELS / coord.y;
	else
		coord.x = LEVELS / coord.y + 1;
	gap = min(board->img->width * 0.05, board->img->height * 0.05);
	if (gap < MINILEVEL_BORDER_THICKNESS)
		gap = MINILEVEL_BORDER_THICKNESS;
	margin_x = (board->img->width - (coord.x * size + (coord.x - 1) * gap)) / 2;
	board->back.pos.x = margin_x;
	board->back.pos.y = board->img->height * 0.12;
	board->back_hover.pos.x = margin_x;
	board->back_hover.pos.y = board->img->height * 0.12;
	set_positions_rest(mlx, board, coord);
}

static int	put_images_to_window(mlx_t *mlx, leaderboard_t *board)
{
	if (mlx_image_to_window(mlx, board->img, 0, 0) < 0)
		return (err("Failed to put leaderboard image to window"));
	if (mlx_image_to_window(mlx, board->title.img, board->title.pos.x,
			board->title.pos.y) < 0)
		return (err("Failed to put leaderboard title image to window"));
	if (mlx_image_to_window(mlx, board->back.img, board->back.pos.x,
			board->back.pos.y) < 0)
		return (err("Failed to put leaderboard back image to window"));
	if (mlx_image_to_window(mlx, board->back_hover.img,
			board->back_hover.pos.x, board->back_hover.pos.y) < 0)
		return (err("Failed to put leaderboard back hover image to window"));
	return (SUCCESS);
}

int	free_half_done_textures(leaderboard_t *board)
{
	mlx_delete_texture(board->title.texture);
	mlx_delete_texture(board->back.texture);
	mlx_delete_texture(board->back_hover.texture);
	return (FAIL);
}

int	init_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int	i;

	if (!load_png_board(board))
		return (FAIL);
	if (!init_images_board(cub3d->mlx, board))
		return (free_half_done_textures(board));
	set_positions(cub3d->mlx, board);
	draw_background(board->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(board->img);
	i = -1;
	while (++i < cub3d->n_levels)
		draw_rectangle(board->img, &board->rect_level[i]);
	if (!put_images_to_window(cub3d->mlx, board))
		return (free_half_done_textures(board));
	set_record_texts(cub3d, board);
	disable_leaderboard(cub3d, board);
	return (SUCCESS);
}
