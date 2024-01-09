
#include "../incl/cub3d.h"

static double	fisheye_correction(cub3d_t *cub3d, int index)
{
	double	perp_dist;
	dvector_t nose_dir;
	nose_dir.y = sin(cub3d->player.angle); 
	nose_dir.x = cos(cub3d->player.angle); 
	dvector_t orto_dir; // unit vector to the right of the player
	orto_dir.x = nose_dir.y;
	orto_dir.y = -nose_dir.x;
	dvector_t ray;
	ray.x = cub3d->rays[index].end.x - cub3d->player.pos.x;
	ray.y = cub3d->rays[index].end.y - cub3d->player.pos.y;
	// projection of ray on ortoDir = ortoDir´*ray * ortoDir 
	double proj_len = orto_dir.x * ray.x + orto_dir.y * ray.y;
	dvector_t ray_proj;
	ray_proj.x = proj_len * orto_dir.x;
	ray_proj.y = proj_len * orto_dir.y;
	// now ray = ray_proj + ray_perp
	dvector_t ray_perp;
	ray_perp.x = ray.x-ray_proj.x;
	ray_perp.y = ray.y-ray_proj.y;
	perp_dist = sqrt(ray_perp.x * ray_perp.x + ray_perp.y * ray_perp.y);
	// calculate the distance in world where the wall fills the screen vertically
	double wall_height = 1;
	double view_fill_dist = wall_height/2.0/sin(to_radians(FOV/2.0));
	// playerDistance / view_fill_dist  =  image height / sceenH
	double window_aspect_ratio = (double)cub3d->img->width/(double)cub3d->img->height;
	return (cub3d->img->height * view_fill_dist / perp_dist * window_aspect_ratio);
}

void	draw_floor(cub3d_t *cub3d)
{
	// double		frustum_near = 1.777771;
	double		frustum_near = 2;
	double		frustum_far = 100;
	dvector_t	far_left;
	dvector_t	far_right;
	dvector_t	near_left;
	dvector_t	near_right;

	far_left.x = cub3d->player.pos.x + frustum_far * cos(cub3d->player.angle - FOV / 2);
	far_left.y = cub3d->player.pos.y + frustum_far * sin(cub3d->player.angle - FOV / 2);
	far_right.x = cub3d->player.pos.x + frustum_far * cos(cub3d->player.angle + FOV / 2);
	far_right.y = cub3d->player.pos.y + frustum_far * sin(cub3d->player.angle + FOV / 2);
	near_left.x = cub3d->player.pos.x + frustum_near * cos(cub3d->player.angle - FOV / 2);
	near_left.y = cub3d->player.pos.y + frustum_near * sin(cub3d->player.angle - FOV / 2);
	near_right.x = cub3d->player.pos.x + frustum_near * cos(cub3d->player.angle + FOV / 2);
	near_right.y = cub3d->player.pos.y + frustum_near * sin(cub3d->player.angle + FOV / 2);

	for (unsigned int y = 0; y < cub3d->img->height / 2; y++)
	{
		dvector_t left;
		dvector_t right;
		double sample_height;
	
		sample_height = (double)y / (double)(cub3d->img->height / 2);
		if (sample_height == 0)
		{
			left.x = near_left.x;
			left.y = near_left.y;
			right.x = near_right.x;
			right.y = near_right.y;
		}
		else
		{
			left.x = near_left.x + (far_left.x - near_left.x) / sample_height;
			left.y = near_left.y + (far_left.y - near_left.y) / sample_height;
			right.x = near_right.x + (far_right.x - near_right.x) / sample_height;
			right.y = near_right.y + (far_right.y - near_right.y) / sample_height;
		}
	
		for (unsigned int x = 0; x < cub3d->img->width; x++)
		{
			double sample_width;
			dvector_t d_sample;
			vector_t sample;

			sample_width = (double)x / (double)cub3d->img->width;
			d_sample.x = left.x + (right.x - left.x) * sample_width;
			d_sample.y = left.y + (right.y - left.y) * sample_height;
			sample.x = floor(d_sample.x);
			sample.y = floor(d_sample.y);
			sample.x = sample.x % cub3d->floor.texture->width;
			sample.y = sample.y % cub3d->floor.texture->height;

			// if (cub3d->printed == FALSE)
			// {
			// 	printf(TERMINAL_GREEN"PLAYER POS\n"TERMINAL_RESET);
			// 	printf("cub3d->player.pos.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, cub3d->player.pos.x);
			// 	printf("cub3d->player.pos.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, cub3d->player.pos.y);
			// 	printf(TERMINAL_GREEN"FRUSTUM\n"TERMINAL_RESET);
			// 	printf("far_left.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, far_left.x);
			// 	printf("far_left.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, far_left.y);
			// 	printf("far_right.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, far_right.x);
			// 	printf("far_right.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, far_right.y);
			// 	printf("near_left.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, near_left.x);
			// 	printf("near_left.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, near_left.y);
			// 	printf("near_right.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, near_right.x);
			// 	printf("near_right.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, near_right.y);
			// 	printf(TERMINAL_GREEN"VECTOR\n"TERMINAL_RESET);
			// 	printf("left.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, left.x);
			// 	printf("left.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, left.y);
			// 	printf("right.x: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, right.x);
			// 	printf("right.y: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, right.y);
			// 	printf(TERMINAL_GREEN"SAMPLE\n"TERMINAL_RESET);
			// 	printf("sample_width: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, sample_width);
			// 	printf("sample_height: "TERMINAL_GREEN"%f\n"TERMINAL_RESET, sample_height);
			// 	printf("sample.x: "TERMINAL_GREEN"%d\n"TERMINAL_RESET, sample.x);
			// 	printf("sample.y: "TERMINAL_GREEN"%d\n"TERMINAL_RESET, sample.y);
			// 	printf(TERMINAL_GREEN"SCREEN POS\n"TERMINAL_RESET);
			// 	printf("x: "TERMINAL_GREEN"%d\n"TERMINAL_RESET, x);
			// 	printf("y: "TERMINAL_GREEN"%d\n"TERMINAL_RESET, y);
			// }
			// if (!cub3d->printed) {printf("Getting color...\n");}
			int color = get_pixel_color(cub3d->floor, sample);
			// if (!cub3d->printed) {printf("Drawing pixel...\n");}
			mlx_put_pixel(cub3d->img, x, y + cub3d->img->height / 2, color);
			// if (!cub3d->printed) {printf("DONE!\n");}
			// if (y == 1 && x == 0) {cub3d->printed = TRUE;}
		}
	}
}

void draw_world(cub3d_t *cub3d)
{
	int			index;
	bool		close;
	double		height;
	dvector_t	start;
	dvector_t	end;


	index = -1;

	draw_floor(cub3d);

	while (++index < (int)cub3d->img->width)
	{
		close = 0;
		if (cub3d->rays[index].length < 0)
			height = cub3d->img->height;
		else if (cub3d->rays[index].length > 100)
			height = 0;
		else
		{
			if (cub3d->settings.fisheye)
				height = 1.0 / (M_PI * 2 * cub3d->rays[index].length * cub3d->fov / 360.0) * cub3d->img->width;
			else
				height = fisheye_correction(cub3d, index);
			if (height > cub3d->img->height)
				close = 1;
		}
		start.x = index;
		start.y = (cub3d->img->height - height) / 2;
		end.x = index;
		end.y = (cub3d->img->height + height) / 2;
		if (end.y == cub3d->img->height)
			end.y--;
		if (cub3d->rays[index].wall == EA)
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == SO)
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == WE)
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == NO)
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == 'A')
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == 'B')
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == 'C')
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == 'D')
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == 'O')
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
		else if (cub3d->rays[index].wall == 'G')
		{
			if (close)
			{
				start.y = 0;
				end.y = cub3d->img->height - 1;
			}
			draw_vertical_line(cub3d->img, start, end, WHITE);
		}
	}
}
