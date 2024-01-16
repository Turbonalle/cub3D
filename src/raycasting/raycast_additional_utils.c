
#include "../incl/cub3d.h"

dvector_t	init_len(dvector_t start_pos, double dir, vector_t check, dvector_t step_size)
{
	dvector_t		v_ray_1d_length;
	dvector_t		v_ray_dir;

	v_ray_dir.x = cos(to_radians(dir));
	v_ray_dir.y = sin(to_radians(dir));
	if (v_ray_dir.x < 0)
		v_ray_1d_length.x = (start_pos.x - check.x) * step_size.x;
	else
		v_ray_1d_length.x = (check.x + 1.0 - start_pos.x) * step_size.x;
	if (v_ray_dir.y < 0)
		v_ray_1d_length.y = (start_pos.y - check.y) * step_size.y;
	else
		v_ray_1d_length.y = (check.y + 1.0 - start_pos.y) * step_size.y;
	return (v_ray_1d_length);
}

vector_t	init_v_step(double dir)
{
	vector_t	v_step;
	dvector_t	v_ray_dir;

	v_ray_dir.x = cos(to_radians(dir));
	v_ray_dir.y = sin(to_radians(dir));
	if (v_ray_dir.x < 0)
		v_step.x = -1;
	else
		v_step.x = 1;
	if (v_ray_dir.y < 0)
		v_step.y = -1;
	else
		v_step.y = 1;
	return (v_step);
}

void	adjust_no_flag(dvector_t *v_ray_1d_length, dvector_t step_size)
{
	if (v_ray_1d_length->x < v_ray_1d_length->y)
		v_ray_1d_length->x += step_size.x;
	else
		v_ray_1d_length->y += step_size.y;
}

int	wall_found(cub3d_t *cub3d, vector_t v_map_check)
{
	return (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& cub3d->level->map[v_map_check.y][v_map_check.x] == WALL);
}

int	goal_found(cub3d_t *cub3d, vector_t v_map_check)
{
	return (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& cub3d->level->map[v_map_check.y][v_map_check.x] == 'G');
}
