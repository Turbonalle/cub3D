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

void	deactivate_key(cub3d_t *cub3d, key_node_t *head, int y, int x)
{
	while (head)
	{
		if (head->pos.x == x && head->pos.y == y)
		{
			head->collected = TRUE;
			cub3d->level->map[y][x] = '0';
			return ;
		}
		head = head->next;
	}
}

void	collect_key(cub3d_t *cub3d, int y, int x)
{
	int	index;

	index = get_key_index(cub3d->level->map[y][x]);
	if (index == -1)
	{
		return ;
	}
	deactivate_key(cub3d, cub3d->level->key_groups[index].keys, y, x);
	cub3d->level->door_groups[index].num_keys_left--;
	draw_key_counts(cub3d);
}

void	item_collected_checker(cub3d_t *cub3d)
{
	int	new_y;
	int	new_x;

	new_y = (int)cub3d->player.new_pos.y;
	new_x = (int)cub3d->player.new_pos.x;
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
		add_record(&cub3d->level->records, (int)(elapsed_time(cub3d) * 1000), ft_strdup("Test Guy"), cub3d->leaderboard.n_entries);
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		draw_start_menu(cub3d, &cub3d->start_menu);
		cub3d->state = STATE_GAMEOVER;
	}
	else
	{
		cub3d->player.pos = cub3d->player.new_pos;
	}
}
