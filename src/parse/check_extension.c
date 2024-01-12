#include "../incl/cub3d.h"

int	check_ext(char *str)
{
	char	*last_slash;
	char	*ext;

	last_slash = ft_strchr(str, '/');
	if (!last_slash)
		ext = ft_strchr(str, '.');
	else
	{
		last_slash = ft_strrchr(str, '/');
		ext = ft_strchr(last_slash, '.');
	}
	if (!ext)
		return (FAIL);
	if (ft_strcmp(ext, ".cub") != 0)
		return (FAIL);
	return (SUCCESS);
}
