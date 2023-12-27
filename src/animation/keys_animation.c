#include "../incl/cub3d.h"

void scale_curr_frame(cub3d_t *cub3d, key_node_t *key, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;
	int			ray_index;

	ft_memset(key->img_curr_frame->pixels, 0, key->img_curr_frame->width * key->img_curr_frame->height * 4);
	row_res = 0;
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < key->img_curr_frame->height)
		{
			while (col_res < src->width * factor)
			{
				// TODO: handle out of limits pixels
				if (col_res < key->img_curr_frame->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					// make sure that source pixel is not out of limits
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					ray_index = (int)(key->pos_screen.x - src->width * factor * 0.5 + col_res);
					if (ray_index >= 0 && ray_index < WIDTH && cub3d->rays[(int)(key->pos_screen.x - src->width * factor * 0.5 + col_res)].length > key->dist_to_player)
						ft_memcpy(key->img_curr_frame->pixels + row_res * key->img_curr_frame->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
				}
				col_res++;
				// Maybe optimise and skip column completely?
			}
		}
		row_res++;
	}
	//printf("pos_screen: x: %d, y: %d\n", pos_screen.x, pos_screen.y);
	key->img_curr_frame->instances[0].x = key->pos_screen.x - src->width * factor * 0.5;
	key->img_curr_frame->instances[0].y = key->pos_screen.y - src->height * factor * 1.5;
	
	//printf("instance pos: x: %d, y: %d\n", res->instances[0].x, res->instances[0].y);
}

void scale_distraction(cub3d_t *cub3d, distraction_t *distraction, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;
	int			ray_index;

	distraction->img_distraction->instances[0].enabled = TRUE;
	ft_memset(distraction->img_distraction->pixels, 0, distraction->img_distraction->width * distraction->img_distraction->height * 4);
	row_res = 0;
	printf("src width: %d, src height: %d\n", src->width, src->height);
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < distraction->img_distraction->height)
		{
			while (col_res < src->width * factor)
			{
				// TODO: handle out of limits pixels
				if (col_res < distraction->img_distraction->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					// make sure that source pixel is not out of limits
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					ray_index = (int)(distraction->pos_screen.x - src->width * factor * 0.5 + col_res);
					if (ray_index >= 0 && ray_index < WIDTH && cub3d->rays[(int)(distraction->pos_screen.x - src->width * factor * 0.5 + col_res)].length > distraction->dist_to_player)
						ft_memcpy(distraction->img_distraction->pixels + row_res * distraction->img_distraction->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
				}
				col_res++;
				// Maybe optimise and skip column completely?
			}
		}
		row_res++;
	}
	distraction->img_distraction->instances[0].x = distraction->pos_screen.x - src->width * factor * 0.5;
	distraction->img_distraction->instances[0].y = distraction->pos_screen.y - src->height * factor * 1.5;
	printf("distraction pos_screen: x: %d, y: %d\n", distraction->pos_screen.x, distraction->pos_screen.y);
}

void scale_curr_enemy_frame(cub3d_t *cub3d, t_enemy *enemy, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;
	int			ray_index;

	enemy->img_curr_frame->instances[0].enabled = TRUE;
	ft_memset(enemy->img_curr_frame->pixels, 0, enemy->img_curr_frame->width * enemy->img_curr_frame->height * 4);
	row_res = 0;
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < enemy->img_curr_frame->height)
		{
			while (col_res < src->width * factor)
			{
				// TODO: handle out of limits pixels
				if (col_res < enemy->img_curr_frame->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					// make sure that source pixel is not out of limits
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					ray_index = (int)(enemy->pos_screen.x - src->width * factor * 0.5 + col_res);
					if (ray_index >= 0 && ray_index < WIDTH && cub3d->rays[ray_index].length > enemy->dist_to_player)
						ft_memcpy(enemy->img_curr_frame->pixels + row_res * enemy->img_curr_frame->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
					
				}
				col_res++;
				// Maybe optimise and skip column completely?
			}
		}
		row_res++;
	}
	//printf("pos_screen: x: %d, y: %d\n", pos_screen.x, pos_screen.y);
	// printf("drew enemy at a distance: %f\n", enemy->dist_to_player);
	enemy->img_curr_frame->instances[0].x = enemy->pos_screen.x - src->width * factor * 0.5;
	enemy->img_curr_frame->instances[0].y = enemy->pos_screen.y - src->height * factor;
	
}

double	calculate_scale_factor(double dist, double normal_dist)
{
	double	scale_factor;

	if (!dist)
		dist = 1;
	scale_factor = normal_dist / dist;
	return (scale_factor);
}

void	draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
	key_node_t  *tmp;
	double scale_factor;
	//mlx_image_t	*old_img;

	//TODO: handle drawing keys in order of distance
	// printf("draw_keys, curr_frame_num: %i\n", curr_frame_num);
	tmp = cub3d->level->key_groups[group_index].keys;
	while (tmp)
	{
		if (tmp->collected == FALSE && tmp->visible == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = TRUE;
			scale_factor = calculate_scale_factor(tmp->dist_to_player, KEY_NORMAL_SCALE_DISTANCE);
			scale_curr_frame(
				cub3d,
				tmp,
				cub3d->level->key_groups[group_index].textures_frames[curr_frame_num],
				scale_factor);
		}
		else if (tmp->visible == FALSE || tmp->collected == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = FALSE;
		}
		tmp = tmp->next;
	}
}

void	draw_enemies_frames(cub3d_t *cub3d, int index)
{
	double scale_factor;
	mlx_texture_t *frame;

	if (cub3d->enemy[index].visible == TRUE)
	{
		cub3d->enemy[index].img_curr_frame->instances[0].enabled = TRUE;
		scale_factor = calculate_scale_factor(cub3d->enemy[index].dist_to_player, ENEMY_NORMAL_SCALE_DISTANCE);
		if (cub3d->enemy[index].state == IDLE)
			frame = cub3d->frames_idle[cub3d->curr_frame_index_idle];
		else if (cub3d->enemy[index].state == WALKING)
			frame = cub3d->frames_walking[cub3d->curr_frame_index_walking];
		else
			frame = cub3d->frames_idle[cub3d->curr_frame_index_idle];
		scale_curr_enemy_frame(
				cub3d,
				&cub3d->enemy[index],
				frame,
				scale_factor);
	}
	else
	{
		cub3d->enemy[index].img_curr_frame->instances[0].enabled = FALSE;
	}
}

void	draw_enemy_frame(cub3d_t *cub3d, t_enemy *enemy)
{
	double scale_factor;
	mlx_texture_t *frame;

	scale_factor = calculate_scale_factor(enemy->dist_to_player, ENEMY_NORMAL_SCALE_DISTANCE);
	if (enemy->state == IDLE)
		frame = cub3d->frames_idle[cub3d->curr_frame_index_idle];
	else if (enemy->state == WALKING)
		frame = cub3d->frames_walking[cub3d->curr_frame_index_walking];
	else
		frame = cub3d->frames_idle[cub3d->curr_frame_index_idle];
	scale_curr_enemy_frame(
		cub3d,
		enemy,
		frame,
		scale_factor
	);
}

void draw_distraction_frame(cub3d_t *cub3d, distraction_t *distraction)
{
	double scale_factor;

	scale_factor = calculate_scale_factor(distraction->dist_to_player, DISTRACTION_NORMAL_SCALE_DISTANCE);
	scale_distraction(
		cub3d,
		distraction,
		cub3d->distraction_texture,
		scale_factor
	);
}

int	count_not_collected_visible_keys(key_node_t	*keys)
{
	int	count;

	count = 0;
	while (keys)
	{
		if (keys->collected == FALSE && keys->visible == TRUE)
			count++;
		keys = keys->next;
	}
	return (count);
}

int	count_all_not_collected_visible_keys(cub3d_t *cub3d)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		count += count_not_collected_visible_keys(cub3d->level->key_groups[i].keys);
		i++;
	}
	return (count);
}

void	sort_keys_by_dist_to_player(key_node_t **keys)
{
	int			i;
	int			j;
	key_node_t	*tmp;

	i = 0;
	while (keys[i])
	{
		j = i + 1;
		while (keys[j])
		{
			if (keys[i]->dist_to_player < keys[j]->dist_to_player)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void fill_keys_array(cub3d_t *cub3d, key_node_t **keys)
{
	int			i;
	int			j;
	key_node_t	*tmp;

	i = 0;
	j = 0;
	while (i < NUM_DOORS_MAX)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			if (tmp->collected == FALSE && tmp->visible == TRUE)
			{
				keys[j] = tmp;
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

key_node_t	**create_array_of_keys_ordered_by_dist(cub3d_t *cub3d)
{
	key_node_t	**keys;
	int			count;

	count = count_all_not_collected_visible_keys(cub3d);
	keys = malloc(sizeof(key_node_t *) * (count + 1));
	keys[count] = NULL;
	// TODO: handle malloc errors
	fill_keys_array(cub3d, keys);
	sort_keys_by_dist_to_player(keys);
	return (keys);
}

void print_pos_and_dist_ordered_keys(key_node_t **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		// printf("key %d, pos: x: %f, y: %f, dist: %f\n", i, keys[i]->pos.x, keys[i]->pos.y, keys[i]->dist_to_player);
		i++;
	}
}


int	count_visible_enemies(cub3d_t *cub3d)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < cub3d->num_enemies)
	{
		if (cub3d->enemy[i].visible == TRUE)
			count++;
		i++;
	}
	return (count);
}

int count_visible_distractions(cub3d_t *cub3d)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		if (cub3d->level->distractions[i].visible == TRUE)
			count++;
		i++;
	}
	return (count);
}

void	fill_visible_enemies_array(cub3d_t *cub3d, t_enemy **enemies)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub3d->num_enemies)
	{
		if (cub3d->enemy[i].visible == TRUE)
		{
			enemies[j] = &cub3d->enemy[i];
			//cub3d->enemy[i].img_curr_frame->instances[0].enabled = TRUE;
			j++;
		}
		else
		{
			cub3d->enemy[i].img_curr_frame->instances[0].enabled = FALSE;
		}
		i++;
	}
}

void	fill_visible_distractions_array(cub3d_t *cub3d, distraction_t **distractions)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		if (cub3d->level->distractions[i].visible == TRUE)
		{
			distractions[j] = &cub3d->level->distractions[i];
			j++;
		}
		else
		{
			cub3d->level->distractions[i].img_distraction->instances[0].enabled = FALSE;
		}
		i++;
	}
}

void	sort_enemies_by_dist_to_player(t_enemy **enemies)
{
	int			i;
	int			j;
	t_enemy		*tmp;

	i = 0;
	while (enemies[i])
	{
		j = i + 1;
		while (enemies[j])
		{
			if (enemies[i]->dist_to_player < enemies[j]->dist_to_player)
			{
				tmp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void sort_distractions_by_dist_to_player(distraction_t **distractions)
{
	int			i;
	int			j;
	distraction_t		*tmp;

	i = 0;
	while (distractions[i])
	{
		j = i + 1;
		while (distractions[j])
		{
			if (distractions[i]->dist_to_player < distractions[j]->dist_to_player)
			{
				tmp = distractions[i];
				distractions[i] = distractions[j];
				distractions[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_enemy **create_array_of_enemies_ordered_by_dist(cub3d_t *cub3d)
{
	t_enemy		**enemies;
	int			count;

	count = count_visible_enemies(cub3d);
	enemies = malloc(sizeof(t_enemy *) * (count + 1));
	enemies[count] = NULL;
	fill_visible_enemies_array(cub3d, enemies);
	sort_enemies_by_dist_to_player(enemies);
	return (enemies);
}

distraction_t **create_array_of_distractions_ordered_by_dist(cub3d_t *cub3d)
{
	distraction_t	**distractions;
	int				count;

	count = count_visible_distractions(cub3d);
	distractions = malloc(sizeof(distraction_t *) * (count + 1));
	distractions[count] = NULL;
	fill_visible_distractions_array(cub3d, distractions);
	sort_distractions_by_dist_to_player(distractions);
	return (distractions);
}

void print_dist_ordered_enemies(t_enemy **enemies)
{
	int	i;

	i = 0;
	while (enemies[i])
	{
		// printf("enemy %d, dist: %f\n", i, enemies[i]->dist_to_player);
		i++;
	}
}

void assign_z_depth_ordered_by_distance(cub3d_t *cub3d, t_enemy **enemies, key_node_t **keys, distraction_t **distractions)
{
	int	i;
	int j;
	int z;

	i = 0;
	j = 0;
	// Start from z position of the main image
	z = cub3d->img->instances[0].z;
	while (enemies[i] || keys[j])
	{
		z++;
		if (enemies[i])
		{
			if (keys[j])
			{
				if (enemies[i]->dist_to_player > keys[j]->dist_to_player)
				{
					enemies[i]->img_curr_frame->instances->z = z;
					i++;
				}
				else
				{
					keys[j]->img_curr_frame->instances->z = z;
					j++;
				}
			}
			else
				while (enemies[i])
				{
					enemies[i]->img_curr_frame->instances->z = z;
					i++;
					z++;
				}
		}
		else
			while (keys[j])
			{
				keys[j]->img_curr_frame->instances->z = z;
				j++;
				z++;
			}
	}
	// TODO: order this properly
	i = 0;
	while (distractions[i])
	{
		z++;
		printf("distraction %d z %d\n", i, z);
		distractions[i]->img_distraction->instances->z = z;
		i++;
	}
}

void	draw_animated_keys(cub3d_t *cub3d)
{
	int 		i;
	key_node_t	**ordered_keys;
	t_enemy		**ordered_enemies;
	distraction_t	**ordered_distractions;

	cub3d->curr_frame_index_idle = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_ENEMY_IDLE;
	if (cub3d->prev_frame_index_idle != cub3d->curr_frame_index_idle)
	{
		cub3d->curr_frame_index_walking = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_ENEMY_WALKING;
		ordered_keys = create_array_of_keys_ordered_by_dist(cub3d);
		ordered_enemies = create_array_of_enemies_ordered_by_dist(cub3d);
		ordered_distractions = create_array_of_distractions_ordered_by_dist(cub3d);
		assign_z_depth_ordered_by_distance(cub3d, ordered_enemies, ordered_keys, ordered_distractions);
		i = 0;
		while (ordered_enemies[i])
		{
			draw_enemy_frame(cub3d, ordered_enemies[i]);
			i++;
		}
		i = 0;
		while (ordered_distractions[i])
		{
			draw_distraction_frame(cub3d, ordered_distractions[i]);
			i++;
		}
		free(ordered_enemies);
		free(ordered_keys);
		free(ordered_distractions);
		cub3d->prev_frame_index_idle = cub3d->curr_frame_index_idle;
		cub3d->prev_frame_index_walking = cub3d->curr_frame_index_walking;
		i = 0;
		while (i < NUM_DOORS_MAX)
		{
			if (cub3d->level->door_groups[i].num_keys_left > 0)
			{
				cub3d->level->key_groups[i].curr_frame_index = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY;
				if (cub3d->level->key_groups[i].prev_frame_index
					!= cub3d->level->key_groups[i].curr_frame_index)
				{
					draw_keys(cub3d, i, cub3d->level->key_groups[i].curr_frame_index);
					cub3d->level->key_groups[i].prev_frame_index
						= cub3d->level->key_groups[i].curr_frame_index;
				}
			}
			i++;
		}
	}
}
