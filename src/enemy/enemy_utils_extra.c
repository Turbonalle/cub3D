
#include "../incl/cub3d.h"

void	eat(cub3d_t *cub3d, int i)
{
	if (cub3d->enemy[i].target.x != cub3d->level->distraction.x
		|| cub3d->enemy[i].target.y != cub3d->level->distraction.y)
		cub3d->enemy[i].is_eating = 0;
	cub3d->level->distraction_amount -= ENEMY_EATING_SPEED;
	if (cub3d->level->distraction_amount <= 0)
	{
		printf("is done eating at %f\n",cub3d->run_time);
		cub3d->player.thrown = FALSE;
		cub3d->level->distractions[cub3d->level->num_distractions]
			.img_distraction->instances[0].enabled = FALSE;
		cub3d->enemy[i].is_eating = 0;
	}
}

void	spin(cub3d_t *cub3d, int i, double at_target)
{
	double	max_dist;

	if (cub3d->enemy[i].is_spinning == 0 && cub3d->settings.e_behaviour < 2)
	{
		cub3d->enemy[i].angle_start = within_two_pi(cub3d->enemy[i].angle - to_radians(ENEMY_ROT_SPEED));
		cub3d->enemy[i].is_spinning = 1;
	}
	cub3d->enemy[i].angle = within_two_pi(cub3d->enemy[i].angle + to_radians(ENEMY_ROT_SPEED));
	if (cub3d->settings.e_behaviour == 2 || (cub3d->settings.e_behaviour == 1 && fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start) < to_radians(ENEMY_ROT_SPEED)))
	{
		cub3d->enemy[i].angle = to_radians(rand() % 360);
		max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
		enemy_movement_ray(cub3d, cub3d->enemy, i, max_dist);
		while (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < at_target)
		{
			cub3d->enemy[i].angle = to_radians(rand() % 360);
			enemy_movement_ray(cub3d, cub3d->enemy, i, max_dist);
		}
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_walking = 1;
		cub3d->enemy[i].is_spinning = 0;
	}

}

int	not_at_end(ray_t *ray, player_t player, t_enemy *enemy, int i)
{
	double			max_dist;

	max_dist = sqrt(pow(player.pos.x - enemy[i].pos.x, 2) + pow(player.pos.y - enemy[i].pos.y, 2));
	if (ray->length < max_dist)
		return (1);
	return (0);
}