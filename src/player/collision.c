#include "../incl/cub3d.h"

int	is_locked_door(cub3d_t *cub3d, int y, int x)
{
	int	index;

	index = get_door_index(cub3d->level->map[y][x]);
	if (index == -1)
	{
		return (FALSE);
	}
	printf("number of keys left for this door group: %i\n", cub3d->level->door_groups[index].num_keys_left);
	return (cub3d->level->door_groups[index].num_keys_left > 0);
}

int	deactivate_key(cub3d_t *cub3d, key_node_t *head, double y, double x)
{
	while (head)
	{
		printf("key: [%f, %f]\n", head->pos.x, head->pos.y);
		printf("pos: [%f, %f]\n", x, y);
		printf("sum of sqares: %f\n", pow(head->pos.x - x, 2) + pow(head->pos.y - y, 2));
		//printf("distance: %f\n", pow(head->pos.x - x) + pow(head->pos.y - y));
		if ((pow(head->pos.x - x, 2) + pow(head->pos.y - y, 2) < 1) && head->collected == FALSE)
		{
			head->collected = TRUE;
			cub3d->level->map[(int)y][(int)x] = '0';
			return TRUE;
		}
		head = head->next;
	}
	return FALSE;
}

void	collect_key(cub3d_t *cub3d, double y, double x)
{
	int	index;

	index = get_key_index(cub3d->level->map[(int)y][(int)x]);
	if (index == -1 || deactivate_key(cub3d, cub3d->level->key_groups[index].keys, y, x) == FALSE)
	{
		return ;
	}
	cub3d->level->door_groups[index].num_keys_left--;
	draw_key_counts(cub3d);
}

void	item_collected_checker(cub3d_t *cub3d)
{
	double	new_y;
	double	new_x;

	new_y = cub3d->player.new_pos.y;
	new_x = cub3d->player.new_pos.x;
	collect_key(cub3d, new_y, new_x);
}

int	new_pos_is_wall_collision(cub3d_t *cub3d)
{
	return (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL
		|| is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.new_pos.x) == TRUE);
}

int new_pos_is_goal(cub3d_t *cub3d)
{
	return (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == 'G');
}

void collision_checker(cub3d_t *cub3d)
{
	dvector_t	delta;
	int			wall;

	item_collected_checker(cub3d);
	if (new_pos_is_wall_collision(cub3d))
	{
		delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
		delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
		wall = find_end_point(cub3d, cub3d->player, cub3d->player.movement_angle, cub3d->player.new_pos);
		if (wall == WE || wall == EA)
		{
			cub3d->player.new_pos.y = cub3d->player.pos.y + delta.y;
			if (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] != WALL && !is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.pos.x))
				cub3d->player.pos.y = cub3d->player.new_pos.y;
		}
		else if (wall == NO || wall == SO)
		{
			cub3d->player.new_pos.x = cub3d->player.pos.x + delta.x;
			if (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] != WALL && !is_locked_door(cub3d, (int)cub3d->player.pos.y, (int)cub3d->player.new_pos.x))
				cub3d->player.pos.x = cub3d->player.new_pos.x;
		}
	}
	else if (new_pos_is_goal(cub3d))
	{
		add_record(&cub3d->level->records, (int)(elapsed_time(cub3d) * 1000), "Test Guy", cub3d->leaderboard.n_entries);
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		draw_start_menu(cub3d, &cub3d->start_menu);
		cub3d->state = STATE_GAMEOVER;
	}
	else
	{
		cub3d->player.pos = cub3d->player.new_pos;
	}
}
