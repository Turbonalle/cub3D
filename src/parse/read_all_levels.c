#include "../incl/cub3d.h"

static void	free_already_allocated(cub3d_t *cub3d, int i)
{
	while (i >= 0)
	{
		free_list(cub3d->levels[i].map_list);
		i--;
		if (i >= 0)
		{
			printf("freeing BACKUP for level %d on malloc fail\n", i);
			free_backup(cub3d->levels[i]);
		}
	}
	free(cub3d->levels);
}

static char	*create_path(int i)
{
	char	*level_i;
	char	*path;
	char	*full_path;

	level_i = ft_itoa(i);
	if (!level_i)
		return (NULL);
	path = ft_strjoin(LEVEL_PREFIX, level_i);
	if (!path)
		return (free(level_i), NULL);
	full_path = ft_strjoin(path, ".cub");
	if (!full_path)
		return (free(level_i), free(path), NULL);
	free(level_i);
	free(path);
	return (full_path);
}

int	read_all_levels(cub3d_t *cub3d)
{
	int		fd;
	int		i;
	char	*full_path;

	i = 1;
	while (i < LEVELS + 1)
	{
		full_path = create_path(i);
		if (full_path == NULL)
			return (free_already_allocated(cub3d, i), err("Malloc error"));
		fd = open(full_path, O_RDONLY);
		if (fd < 0)
			return (free(full_path), free_already_allocated(cub3d, i),
				err("Failed to open level file"));
		if (!read_cub_file(&cub3d->levels[i], full_path))
			return (free(full_path), free_already_allocated(cub3d, i),
				err("Failed to read level file"));
		close(fd);
		free(full_path);
		i++;
	}
	return (1);
}