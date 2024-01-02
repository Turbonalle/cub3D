
#include "../incl/cub3d.h"

static void	draw_enemy(cub3d_t *cub3d, double dir_to_enemy, int index)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to_enemy);
	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad >= cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	if (dir_as_rad == 0)
	{
		i = 1;
		while (i < (int)cub3d->img->width - 1)
		{
			if (cub3d->rays[i].angle > cub3d->rays[i + 1].angle)
				break ;
			i++;
		}
	}
	cub3d->enemy[index].dist_to_player = dist_between_d_vectors(cub3d->enemy[index].pos, cub3d->player.pos);
	cub3d->enemy[index].pos_screen.x = i;
	cub3d->enemy[index].pos_screen.y = cub3d->img->height / 2 + (cub3d->img->height / 2) / cub3d->enemy[index].dist_to_player * 2;
}

static void	see_enemy(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;
	double	max_dist;
	double	dir_to_enemy;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	max_dist = sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2));
	dir_to_enemy = within_360((atan2(cub3d->enemy[i].pos.y - cub3d->player.pos.y, cub3d->enemy[i].pos.x - cub3d->player.pos.x) * 180 / M_PI));
	cub3d->enemy[i].visible = FALSE;
	if (angle_max < angle_min)	// check if 0 radians is within the fov
	{
		if (cub3d->fov < 360 && dir_to_enemy > angle_max && dir_to_enemy < angle_min)	// check if enemy is outside the fov
		{
			if (cub3d->enemy[i].is_hunting)
				enemy_cursor(cub3d, dir_to_enemy, dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->player.pos));
		}
		else if (ray_to_enemy(cub3d, dir_to_enemy, max_dist))	// enemy is within the fov
		{
			cub3d->enemy[i].visible = TRUE;
			draw_enemy(cub3d, dir_to_enemy, i);
		}
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to_enemy < angle_min || dir_to_enemy > angle_max))	// check if enemy is outside the fov
		{
			if (cub3d->enemy[i].is_hunting)
				enemy_cursor(cub3d, dir_to_enemy, dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->player.pos));
		}
		else if (ray_to_enemy(cub3d, dir_to_enemy, max_dist))	// enemy is within the fov
		{
			cub3d->enemy[i].visible = TRUE;
			draw_enemy(cub3d, dir_to_enemy, i);
		}
	}
	return ;
}

static void	see_keys(cub3d_t *cub3d, int i)
{
	double		dir_to_key;
	key_node_t	*temp;

	temp = cub3d->level->key_groups[i].keys;
	while (temp)
	{
		dir_to_key = within_360((atan2(temp->pos.y - cub3d->player.pos.y,
						temp->pos.x - cub3d->player.pos.x) * 180 / M_PI));
		if (temp->collected == 0)
			see_key(cub3d, dir_to_key, temp);
		temp = temp->next;
	}
}

static void	check_distraction(cub3d_t *cub3d, int i)
{
	double		dir_to_distraction;

	dir_to_distraction = within_360((atan2(cub3d->level->distractions[i].pos.y
					- cub3d->player.pos.y, cub3d->level->distractions[i].pos.x
					- cub3d->player.pos.x) * 180 / M_PI));
	if (cub3d->level->distractions[i].collected == FALSE)
		see_distraction(cub3d, dir_to_distraction, i);
}

void	draw_enemies(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		see_enemy(cub3d, i);
		i++;
	}
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->door_groups[i].num_keys_left)
		{
			see_keys(cub3d, i);
		}
		i++;
	}
	i = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		check_distraction(cub3d, i);
		i++;
	}
}
