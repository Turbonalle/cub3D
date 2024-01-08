
#include "../incl/cub3d.h"

int	check_collisions(cub3d_t *cub3d, int i)
{
	int			j;
	dvector_t	new_pos;

	j = -1;
	cub3d->enemy[i].is_walking = 0;
	new_pos.x = cub3d->enemy[i].pos.x + cos(cub3d->enemy[i].angle) * ENEMY_SPEED * (1 + cub3d->settings.e_speed);
	new_pos.y = cub3d->enemy[i].pos.y + sin(cub3d->enemy[i].angle) * ENEMY_SPEED * (1 + cub3d->settings.e_speed);
	while (j++ < cub3d->num_enemies)
	{
		if (i == j)
			continue ;
		if (dist_between_d_vectors(new_pos, cub3d->enemy[j].pos) < 1.3 * ENEMY_RADIUS)
			return (1);
	}
	if (cub3d->enemy[i].angle > M_PI * 15 / 8 || cub3d->enemy[i].angle < M_PI * 1 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (0);
		}
	}
	else if (cub3d->enemy[i].angle < M_PI * 3 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x)) == TRUE))
		{
			return (0);
		}
	}
	else if (cub3d->enemy[i].angle < M_PI * 5 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x)) == TRUE))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (0);
		}
	}
	else if (cub3d->enemy[i].angle < M_PI * 7 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
	}
	else if (cub3d->enemy[i].angle < M_PI * 9 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y + ENEMY_RADIUS)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y + ENEMY_RADIUS), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.x = new_pos.x;
			return (0);
		}
	}
	else if (cub3d->enemy[i].angle < M_PI * 11 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)) == TRUE))
		{
			return (0);
		}
	}
	else if (cub3d->enemy[i].angle < M_PI * 13 / 8)
	{
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x - ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x - ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)) == TRUE))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			cub3d->enemy[i].pos.y = new_pos.y;
			return (0);
		}
	}
	else
	{
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y - ENEMY_RADIUS)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y - ENEMY_RADIUS), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
		if ((cub3d->level->map[(int)(new_pos.y)][(int)(new_pos.x + ENEMY_RADIUS)] == WALL
			|| is_locked_door(cub3d, (int)(new_pos.y), (int)(new_pos.x + ENEMY_RADIUS)) == TRUE))
		{
			return (0);
		}
	}
	cub3d->enemy[i].pos = new_pos;
	return (0);
}

void	enemy_advance(cub3d_t *cub3d, int i)
{
	if (check_collisions(cub3d, i) == 1)
		return ;
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
	cub3d->enemy[i].dir_player = within_360(atan2(cub3d->player.pos.y
				- cub3d->enemy[i].pos.y, cub3d->player.pos.x
				- cub3d->enemy[i].pos.x) * 180 / M_PI);
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
