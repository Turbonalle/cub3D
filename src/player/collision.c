#include "../incl/cub3d.h"

int	is_locked_door(cub3d_t *cub3d, int y, int x)
{
	int index;
	
	index = get_door_index(cub3d->map[y][x]);
	if (index == -1)
	{
		return (FALSE);
	}
	printf("number of keys left for this door group: %i\n",cub3d->door_groups[index].num_keys_left);
	return (cub3d->door_groups[index].num_keys_left > 0);
}

void	deactivate_key(cub3d_t *cub3d, key_node_t	*head, int y, int x)
{
	while(head)
	{
		printf("comparing key position [%i, %i] to [%i, %i]\n", head->pos.x, head->pos.y, x, y);
		if (head->pos.x == x && head->pos.y == y)
		{
			head->collected = TRUE;
			cub3d->map[y][x] = '0';
			return;
		}
		head = head->next;
	}
}

void	collect_key(cub3d_t *cub3d, int y, int x)
{
	int index;

	printf("before getting key index\n");
	index = get_key_index(cub3d->map[y][x]);
	printf("after getting key index\n");
	if (index == -1)
	{
		return ;
	}
	deactivate_key(cub3d, cub3d->key_groups[index].keys, y, x);
	cub3d->door_groups[index].num_keys_left--;
}

void	item_collected_checker(cub3d_t *cub3d)
{
	collect_key(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.new_pos.x);
}

void collision_checker(cub3d_t *cub3d)
{
	dvector_t delta;
	int wall;

	if (cub3d->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL || is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.new_pos.x))
	{
		delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
		delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
		wall = find_end_point(cub3d, &cub3d->player, cub3d->player.movement_angle, &cub3d->player.new_pos);
		if (wall == WE || wall == EA)
		{
			cub3d->player.new_pos.y = cub3d->player.pos.y + delta.y;
			if (cub3d->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] != WALL)
				cub3d->player.pos.y = cub3d->player.new_pos.y;
		}
		else if (wall == NO || wall == SO)
		{
			cub3d->player.new_pos.x = cub3d->player.pos.x + delta.x;
			if (cub3d->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] != WALL)
				cub3d->player.pos.x = cub3d->player.new_pos.x;
		}
	}
	else
		cub3d->player.pos = cub3d->player.new_pos;
}
