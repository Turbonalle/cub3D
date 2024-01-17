/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_additional.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:59:38 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 12:59:41 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_collisions(cub3d_t *cub3d, int i)
{
	dvector_t	new_pos;

	cub3d->enemy[i].is_walking = 0;
	new_pos = set_new_pos(cub3d, i);
	if (check_each_other(cub3d, i, new_pos))
		return (1);
	if (check_first_eight(cub3d, i, new_pos))
		return (1);
	else if (check_second_eight(cub3d, i, new_pos))
		return (1);
	else if (check_third_eight(cub3d, i, new_pos))
		return (1);
	else if (check_fourth_eight(cub3d, i, new_pos))
		return (1);
	else if (check_fifth_eight(cub3d, i, new_pos))
		return (1);
	else if (check_sixth_eight(cub3d, i, new_pos))
		return (1);
	else if (check_seventh_eight(cub3d, i, new_pos))
		return (1);
	else if (check_eighth_eight(cub3d, new_pos))
		return (1);
	cub3d->enemy[i].pos = new_pos;
	return (0);
}

void	enemy_advance(cub3d_t *cub3d, int i)
{
	if (check_collisions(cub3d, i) == 1)
	{
		cub3d->enemy[i].angle = within_two_pi(atan2(cub3d->enemy[i].target.y
					- cub3d->enemy[i].pos.y, cub3d->enemy[i].target.x
					- cub3d->enemy[i].pos.x));
		return ;
	}
	cub3d->enemy[i].is_walking = 1;
}

char	*create_file_path(int i, char *path)
{
	char	*file_name;
	char	*file_ext;
	char	*file_path;

	file_name = ft_itoa(i + 1);
	if (!file_name)
		return (NULL);
	file_ext = ft_strjoin(file_name, ".png");
	if (!file_ext)
		return (free(file_name), NULL);
	file_path = ft_strjoin(path, file_ext);
	if (!file_ext)
		return (free(file_name), free(file_ext), NULL);
	free(file_name);
	free(file_ext);
	return (file_path);
}

static int	check_angles(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	if (angle_max < angle_min)
	{
		if (cub3d->enemy[i].dir_player > angle_max
			&& cub3d->enemy[i].dir_player < angle_min)
			return (1);
	}
	else
	{
		if (cub3d->enemy[i].dir_player < angle_min
			|| cub3d->enemy[i].dir_player > angle_max)
			return (1);
	}
	return (0);
}

int	check_if_player_is_seen(cub3d_t *cub3d, int i)
{
	double	at_target;

	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	if (check_angles(cub3d, i))
		return (0);
	else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy, i)
		&& (dist_between_d_vectors(cub3d->player.pos,
				cub3d->enemy[i].pos) > at_target))
	{
		cub3d->enemy[i].is_hunting = TRUE;
		return (1);
	}
	else
		return (0);
}
