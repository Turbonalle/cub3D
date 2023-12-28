
#include "../incl/cub3d.h"

double lerp(double y0, double y1, double x0, double x1, double x)
{
	return (y0 + (y1 - y0) * ((x - x0) / (x1 - x0)));
}

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

void draw_world(cub3d_t *cub3d)
{
	int		index;
	bool	close;
	double	min_dist;
	double	max_dist;
	double	height;
	double	roomH;
	double	screenH;
	double	fovArc;
	dvector_t start;
	dvector_t end;

	min_dist = 0;
	max_dist = 100;
	index = -1;
	roomH = 3;

	while (++index < (int)cub3d->img->width)
	{
		close = 0;
		if (cub3d->rays[index].length < min_dist)
			height = cub3d->img->height;
		else if (cub3d->rays[index].length > max_dist)
			height = 0;
		else
		{
			{
				if (cub3d->settings.fisheye)
				{
					fovArc = M_PI * 2 * cub3d->rays[index].length * cub3d->fov / 360.0;
					screenH = 1.0 / fovArc * cub3d->img->width * roomH;
				}
				else
					screenH = fisheye_correction(cub3d, index);
				height = screenH;
				if (height > cub3d->img->height)
					close = 1;
			}
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
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, BLUE);
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
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, GREEN);
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
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, RED_LIGHT);
		}
		else if (cub3d->rays[index].wall == 'B')
		{
			if (close)
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, GREEN);
		}
		else if (cub3d->rays[index].wall == 'C')
		{
			if (close)
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, YELLOW_PALE);
		}
		else if (cub3d->rays[index].wall == 'D')
		{
			if (close)
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, TURQUOISE);
		}
		else if (cub3d->rays[index].wall == 'G')
		{
			if (close)
			{
				start.y = 0;
				end.y = cub3d->img->height;
			}
			draw_vertical_line(cub3d->img, start, end, WHITE);
		}
	}
}
