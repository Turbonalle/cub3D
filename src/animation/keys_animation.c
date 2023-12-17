#include "../incl/cub3d.h"

void scale_curr_frame(mlx_image_t *res, mlx_image_t *src, double factor, vector_t pos_world)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;

	//int		pixel;	
	//int i;

	row_res = 0;
	printf("factor: %f\n", factor);
	printf("RES height: %f, width: %f\n", src->height * factor, src->width * factor);
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
				//printf("Before rounding row: %f, col: %f\n", row_res / factor, col_res / factor);
				
				//printf("After rounding row: %u, col: %u\n", row_src, col_src);
				//ft_memcpy(&pixel, src->pixels + row_src * src->width * 4 + col_src * 4, 4);
				//printf("res[%u, %u] = src[%u, %u]\n", row_res, col_res, row_src, col_src);
				//mlx_put_pixel(res, col_res, row_res, pixel);
				
				/* printf("[%u, %u] : res pixels[%u] = src pixels[%u]\n",
				row_res,
				col_res,
				row_res * res->width * 4 + col_res * 4,
				row_src * src->width * 4 + col_src * 4); */
				/* i = 0;
				while (i < 4)
				{
					
					res->pixels[row_res * res->width * 4 + col_res * 4 + i]
						= src->pixels[row_src * src->width * 4 + col_src * 4 + i];
					i++;
				} */
				col_res++;
				// Maybe optimise and skip column complately?
			}
		}
		row_res++;
	}
	printf("pos_world: x: %d, y: %d\n", pos_world.x, pos_world.y);
	res->instances[0].x = pos_world.x - src->width * factor * 0.5;
	res->instances[0].y = pos_world.y - src->height * factor * 0.5;
	printf("instance pos: x: %d, y: %d\n", res->instances[0].x, res->instances[0].y);
}

void	disable_frames_except(mlx_image_t **img_frames, int except, int instance_index)
{
	int	i;

	//printf("disable_frames_except called, exception is %d\n", except);
	i = 0;
	while (i < NUM_FRAMES_KEY)
	{
		if (i != except)
			img_frames[i]->instances[instance_index].enabled = false;
		else
			img_frames[i]->instances[instance_index].enabled = true;
		i++;
	}
}

double	calculate_scale_factor(dvector_t key_pos, dvector_t player_pos)
{
	double	dist;
	double	scale_factor;

	dist = sqrt(pow(key_pos.x - player_pos.x, 2) + pow(key_pos.y - player_pos.y, 2));
	scale_factor = KEY_NORMAL_SCALE_DISTANCE / dist;
	return (scale_factor);
}

void	draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
	key_node_t  *tmp;
	double scale_factor;
	//mlx_image_t	*old_img;

	printf("draw_keys, curr_frame_num: %i\n", curr_frame_num);
	tmp = cub3d->level->key_groups[group_index].keys;
	while (tmp)
	{
		if (tmp->collected == FALSE && tmp->visible == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = TRUE;
			scale_factor = calculate_scale_factor(tmp->pos, cub3d->player.pos);
			//old_img = tmp->img_curr_frame;
			/* tmp->img_curr_frame = scale_img(cub3d,
				cub3d->level->key_groups[group_index].img_frames[curr_frame_num],
				scale_factor); */
			scale_curr_frame(
				tmp->img_curr_frame,
				cub3d->level->key_groups[group_index].img_frames[curr_frame_num],
				scale_factor,
				tmp->pos_world);
			
			//mlx_image_to_window(cub3d->mlx, tmp->img_curr_frame, tmp->pos_world.x, tmp->pos_world.y);
			//mlx_image_to_window(cub3d->mlx, cub3d->level->key_groups[group_index].img_frames[curr_frame_num], tmp->pos_world.x, tmp->pos_world.y);
			//mlx_delete_image(cub3d->mlx, old_img);
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
			printf("key group %d has %d keys left\n", i, cub3d->level->door_groups[i].num_keys_left);
			/* printf("run_time: %f, divided byy %f : %f, after mod: %d\n", cub3d->run_time, ANIMATION_INTERVAL_MS * 1000, cub3d->run_time / ANIMATION_INTERVAL_MS * 1000, (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY); */

			// set current frame based on time
			cub3d->level->key_groups[i].curr_frame_index = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY;
			if (cub3d->level->key_groups[i].prev_frame_index
				!= cub3d->level->key_groups[i].curr_frame_index)
			{
				draw_keys(cub3d, i, cub3d->level->key_groups[i].curr_frame_index);
				cub3d->level->key_groups[i].prev_frame_index
					= cub3d->level->key_groups[i].curr_frame_index;
			}
			

			//disable_frames_except(cub3d->level->key_groups[i].img_frames, curr_frame_num, valid_key_group_index);
			// TODO: improve to disable only necessary frames
		}
		i++;
	}
}
