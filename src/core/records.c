#include "../incl/cub3d.h"

void	delete_last_record(cub3d_t *cub3d, mlx_t *mlx, record_t **records)
{
	record_t	*ptr;
	record_t	*prev;

	ptr = *records;
	while (ptr->next)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	prev->next = NULL;
	if (cub3d->state != STATE_START)
	{
		mlx_delete_image(mlx, ptr->text_name);
		mlx_delete_image(mlx, ptr->text_time);
	}
	free_record(ptr);
}

int	add_record(cub3d_t *cub3d, record_t **records, int time, char* name, int n_entries)
{
	record_t	*new;
	record_t	*temp;
	int			i;

	new = new_record(time, name);
	if (!new)
		return (err("Failed to malloc new record"));
	
	// if no records yet
	if (!*records)
	{
		*records = new;
		return (SUCCESS);
	}

	// if new record is better than the first record
	if (time < (*records)->time)
	{
		new->next = *records;
		*records = new;
		return (SUCCESS);
	}

	temp = *records;
	i = 1;
	while (temp->next && temp->next->time < time && i < n_entries)
	{
		temp = temp->next;
		i++;
	}
	if (i > n_entries)		// if new record is worse than the last record
	{
		free_record(new);
	}
	if (temp->next) 	// if new record is better than a record in the middle
	{
		new->next = temp->next;
		temp->next = new;
	}
	else					// if new record is better than the last record
		temp->next = new;
	i = count_records(*records);
	while (i > n_entries)
	{
		delete_last_record(cub3d, cub3d->mlx, records);
		i = count_records(*records);
	}
	return (SUCCESS);
}

int	set_records(cub3d_t *cub3d, level_t *level, char **line, int n_entries, int fd)
{
	char	*name;
	int		time;

	while (*line && **line != '\n')
	{
		if (!get_record_time(*line, &time))
			return (err("Failed to get time string"));
		if (!get_record_name(*line, &name))
			return (err("Failed to get name string"));
		add_record(cub3d, &level->records, time, name, n_entries);
		free(*line);
		*line = get_next_line(fd);
	}
	return (SUCCESS);
}

int	free_half_done(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < LEVELS + 1)
	{
		free_list(cub3d->levels[i].map_list);
		free_backup(cub3d->levels[i]);
		i++;
	}
	free(cub3d->levels);
	free(cub3d->rays);
	free_prev_start_menu(&cub3d->start_menu, 9);
	free_prev_level_menu(&cub3d->level_menu, LEVELS, 4);
	free_prev_name_menu(&cub3d->name_menu, 2);
	free_prev_gameover_menu(&cub3d->gameover_menu, 8);
	mlx_delete_texture(cub3d->intro.texture);
	i = -1;
	while (++i < HEARTS)
	{
		mlx_delete_texture(cub3d->hearts[i].full.texture);
		mlx_delete_texture(cub3d->hearts[i].empty.texture);
	}
	mlx_delete_texture(cub3d->shroom->shroom.texture);
	mlx_delete_image(cub3d->mlx, cub3d->img);
	mlx_delete_texture(cub3d->distraction_thrown_texture);
	mlx_delete_texture(cub3d->distraction_texture);
	free_textures_before_failed(cub3d->door, 5);
	mlx_delete_texture(cub3d->pause_menu.title.texture);
	return (0);
}

int	read_records(cub3d_t *cub3d)
{
	char	*line;
	int		fd;
	int		i;

	//TODO: remove levels parameter
	fd = open(RECORD_FILE, O_RDONLY);
	if (fd < 0)
	{
		free_all(cub3d, -1);
		return (err("Failed to open records file"));
	}
	i = 0;
	line = get_next_line(fd);
	while (line && ++i < cub3d->n_levels + 1)
	{
		if (!set_records(cub3d, &cub3d->levels[i], &line, cub3d->leaderboard.n_entries, fd))
		{
			free_all(cub3d, -1);
			free(line);
			return (err("Failed to set records"));
		}
		if (line && *line == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	free(line);
	close(fd);
	return (SUCCESS);
}
