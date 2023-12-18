#include "../incl/cub3d.h"

void scale_curr_frame(mlx_image_t *res, mlx_texture_t *src, double factor, vector_t pos_screen)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;

	//int		pixel;	
	//int i;

	row_res = 0;
	//printf("factor: %f\n", factor);
	//printf("RES height: %f, width: %f\n", src->height * factor, src->width * factor);
	ft_memset(res->pixels, 0, res->width * res->height * 4);
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < res->height)
		{
			while (col_res < src->width * factor)
			{
				// TODO: handle out of limits pixels
				if (col_res < res->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					// make sure that source pixel is not out of limits
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					ft_memcpy(res->pixels + row_res * res->width * 4 + col_res * 4,
						src->pixels + row_src * src->width * 4 + col_src * 4,
						4);
				}
				col_res++;
				// Maybe optimise and skip column completely?
			}
		}
		row_res++;
	}
	// printf("pos_screen: x: %d, y: %d\n", pos_screen.x, pos_screen.y);
	res->instances[0].x = pos_screen.x - src->width * factor * 0.5;
	res->instances[0].y = pos_screen.y - src->height * factor * 1.5;
	// printf("instance pos: x: %d, y: %d\n", res->instances[0].x, res->instances[0].y);
}

double	calculate_scale_factor(double dist)
{
	double	scale_factor;

	if (!dist)
		dist = 1;
	scale_factor = KEY_NORMAL_SCALE_DISTANCE / dist;
	return (scale_factor);
}

void	draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
	key_node_t  *tmp;
	double scale_factor;
	//mlx_image_t	*old_img;

	//TODO: handle drawing keys in order of distance
	//printf("draw_keys, curr_frame_num: %i\n", curr_frame_num);
	tmp = cub3d->level->key_groups[group_index].keys;
	while (tmp)
	{
		if (tmp->collected == FALSE && tmp->visible == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = TRUE;
			scale_factor = calculate_scale_factor(tmp->dist_to_player);
			scale_curr_frame(
				tmp->img_curr_frame,
				cub3d->level->key_groups[group_index].textures_frames[curr_frame_num],
				scale_factor,
				tmp->pos_screen);
		}
		else if (tmp->visible == FALSE || tmp->collected == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = FALSE;
		}
		tmp = tmp->next;
	}
}

void	draw_animated_keys(cub3d_t *cub3d)
{
	int i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->door_groups[i].num_keys_left > 0)
		{
			//printf("key group %d has %d keys left\n", i, cub3d->level->door_groups[i].num_keys_left);
			// set current frame based on time
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
