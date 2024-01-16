/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors_and_keys.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:15:13 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 16:55:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	init_key_frames(key_group_t *key_group)
{
	int		i;
	char	*file_path;

	key_group->textures_frames = ft_calloc(NUM_FRAMES_KEY,
			sizeof(mlx_texture_t *));
	if (!key_group->textures_frames)
		return (FAIL);
	i = 0;
	while (i < NUM_FRAMES_KEY)
	{
		file_path = create_file_path(i, key_group->texture_dir);
		if (!file_path)
			return (free(key_group->textures_frames), FAIL);
		key_group->textures_frames[i] = mlx_load_png(file_path);
		free(file_path);
		if (!key_group->textures_frames[i])
		{
			while (i >= 0)
				mlx_delete_texture(key_group->textures_frames[i--]);
			free(key_group->textures_frames);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	create_images(cub3d_t *cub3d, int i, int active_key_groups)
{
	cub3d->level->key_groups[i].key_icon_coords.x = cub3d->mlx->width * 0.035;
	cub3d->level->key_groups[i].key_icon_coords.y = cub3d->mlx->height * 0.907
		- cub3d->mlx->height * 0.05 * active_key_groups;
	cub3d->level->key_groups[i].img_key_icon = mlx_texture_to_image(cub3d->mlx,
			cub3d->level->key_groups[i].texture_key_icon);
	if (!cub3d->level->key_groups[i].img_key_icon
		|| (mlx_image_to_window(cub3d->mlx,
				cub3d->level->key_groups[i].img_key_icon,
				cub3d->level->key_groups[i].key_icon_coords.x,
				cub3d->level->key_groups[i].key_icon_coords.y
			) < 0))
		return (err("Failed to create key count image"));
	if (!init_key_frames(&cub3d->level->key_groups[i]))
	{
		return (FAIL);
	}
	return (SUCCESS);
}

int	init_doors_and_keys(cub3d_t *cub3d)
{
	int	i;
	int	count;
	int	active_key_groups;

	init_door_values(cub3d);
	if (set_indexes(cub3d, 0) == FAIL)
	{
		return (free_doors_and_keys(cub3d));
	}
	if (load_door_textures(cub3d) == FAIL)
		return (free_on_fail(cub3d));
	i = -1;
	active_key_groups = 0;
	while (++i < NUM_DOORS_MAX)
	{
		count = count_keys(cub3d, i);
		if (count == -1)
			return (free_on_fail(cub3d));
		cub3d->level->key_groups[i].num_keys_total = count;
		if (count && (create_images(cub3d, i, active_key_groups++) == FAIL))
			return (free_on_fail(cub3d));
	}
	if (!draw_key_counts(cub3d))
		return (free_on_fail(cub3d));
	return (SUCCESS);
}
