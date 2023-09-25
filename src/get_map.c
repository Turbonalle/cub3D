#include "../incl/cub3d.h"

int read_map_file(cub3d_t *cub3d, char *map_path)
{
	int fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (err("Failed to open map file"));
	get_elements(cub3d, fd);
	// if (!get_elements(cub3d, fd) || !get_map(cub3d, fd))
	// 	handle_file_error(fd);
	close(fd);
	return (0);
}