#include "../incl/cub3d.h"

static int	init_dist(cub3d_t *cub3d, int i, int j, int distr_index)
{
	cub3d->level->distractions[distr_index].pos.x = j + 0.5;
	cub3d->level->distractions[distr_index].pos.y = i + 0.5;
	cub3d->level->distractions[distr_index].collected = FALSE;
	cub3d->level->distractions[distr_index].thrown = FALSE;
	cub3d->level->distractions[distr_index].visible = FALSE;
	cub3d->level->distractions[distr_index].pos_screen.x = -WIDTH;
	cub3d->level->distractions[distr_index].pos_screen.y = -HEIGHT;
	cub3d->level->distractions[distr_index].dist_to_player = 100;
	cub3d->level->distractions[distr_index].img_distraction = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->level->distractions[distr_index].img_distraction)
		return (-1);
	mlx_image_to_window(cub3d->mlx, cub3d->level->distractions[distr_index].img_distraction, 0, 0);
	return (distr_index + 1);
}

int	init_distractions(cub3d_t *cub3d)
{
	int	i;
	int	j;
	int	distr_index;

	if (cub3d->level->num_distractions == 0)
		return (1);
	cub3d->level->distractions = malloc(sizeof(distraction_t) * (cub3d->level->num_distractions + 1));
	if (!cub3d->level->distractions)
		return (FAIL);
	i = 0;
	distr_index = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (cub3d->level->map[i][j] == 'm')
			{
				distr_index = init_dist(cub3d, i, j, distr_index);
				if (distr_index == -1)
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
