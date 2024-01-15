#include "../incl/cub3d.h"

double	calculate_scale_factor(double dist, double normal_dist)
{
	double	scale_factor;

	if (!dist)
		dist = 1;
	scale_factor = normal_dist / dist;
	return (scale_factor);
}

int	get_enemy_dir(t_enemy *enemy)
{
	double	enemy_relative_dir;
	
	enemy_relative_dir = within_360((180 / M_PI * enemy->angle) - enemy->dir_player);
	if (enemy_relative_dir < 30)
		return (STRAIGHT);
	else if (enemy_relative_dir < 65)
		return (LEFT_45);
	else if (enemy_relative_dir < 100)
		return (LEFT);
	else if (enemy_relative_dir < 260)
		return (AWAY);
	else if (enemy_relative_dir < 295)
		return (RIGHT);
	else if (enemy_relative_dir < 330)
		return (RIGHT_45);
	else
		return (STRAIGHT);
}
