/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:32:43 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 12:43:06 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_non_speedrun(t_cub3d *cub3d, t_vector coord, int size)
{
	double	row;
	double	column;
	int		i;

	i = -1;
	while (++i < cub3d->num_enemies)
	{
		coord.y = ((cub3d->enemy[i].pos.y - 0.5) * cub3d->minimap.tile_size)
			- (size / 2);
		coord.x = ((cub3d->enemy[i].pos.x - 0.5) * cub3d->minimap.tile_size)
			- (size / 2);
		if (!next_to_hidden(cub3d, cub3d->enemy[i].pos.y,
				cub3d->enemy[i].pos.x))
		{
			draw_square(cub3d->minimap.img, coord, size * 4,
				cub3d->minimap.color_enemy);
		}
	}
	row = -1;
	while (++row < cub3d->level->map_rows)
	{
		column = -1;
		while (++column < cub3d->level->map_columns)
			draw_extras(cub3d, row, column);
	}
}

void	draw_minimap_player(t_cub3d *cub3d)
{
	t_vector	coord;
	int			size;

	size = cub3d->minimap.tile_size / 4;
	if (size < 1)
		size = 1;
	coord.y = (cub3d->player.pos.y * cub3d->minimap.tile_size) - (size / 2);
	coord.x = (cub3d->player.pos.x * cub3d->minimap.tile_size) - (size / 2);
	draw_square(cub3d->minimap.img, coord, size, cub3d->minimap.color_player);
	if (cub3d->speedrun == 0)
		draw_non_speedrun(cub3d, coord, size);
}

void	draw_minimap_playerdir(t_cub3d *cub3d)
{
	t_dvector	end;

	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
	end.x = cub3d->minimap.player_pos.x + (cub3d->player.dir.x
			* cub3d->minimap.tile_size / 2);
	end.y = cub3d->minimap.player_pos.y + (cub3d->player.dir.y
			* cub3d->minimap.tile_size / 2);
	draw_line(cub3d->minimap.img, cub3d->minimap.player_pos, end,
		cub3d->minimap.color_playerdir);
}

void	draw_fov(t_cub3d *cub3d)
{
	t_dvector		end;
	unsigned int	i;

	i = 0;
	while (i < cub3d->img->width)
	{
		end.x = cub3d->minimap.player_pos.x + cos(cub3d->rays[i].angle)
			* cub3d->rays[i].length * cub3d->minimap.tile_size;
		end.y = cub3d->minimap.player_pos.y + sin(cub3d->rays[i].angle)
			* cub3d->rays[i].length * cub3d->minimap.tile_size;
		draw_line(cub3d->minimap.img, cub3d->minimap.player_pos, end,
			cub3d->minimap.color_fov);
		i++;
	}
}
