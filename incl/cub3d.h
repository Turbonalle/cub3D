#ifndef CUB3D_H
# define CUB3D_H
# include "colors.h"
# include "terminal_colors.h"
# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stdio.h>

# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1

# define MAP_ALL_ELEMENTS "NSEW 01"
# define MAP_DIRECTIONS "NSEW"
# define MAP_ELEMENTS "01"

enum elements
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

// prototype map_node_t
typedef struct map_node_s map_node_t;

typedef struct texture_s
{
	char	*path;
	int		*img;
	int		width;
	int		height;
}			texture_t;

typedef struct vector_s
{
	int	x;
	int	y;
}		vector_t;

typedef struct dvector_t
{
	double	x;
	double	y;
}			dvector_t;

typedef struct player_s
{
	dvector_t	pos;
	dvector_t	dir;
	double		angle;
}				player_t;

typedef struct map_node_s
{
	char		*line;
	map_node_t	*next;
}			map_node_t;

typedef struct cub3d_s
{
	vector_t	starting_pos;
	char		starting_dir;
	map_node_t	*map_list;
	int			nodes;
	char		**map;
	texture_t	texture[4];
	int			floor_color;
	int			ceiling_color;
	int			element_found[6];
}			cub3d_t;

// main.c
void free_info(char **info);
int err(char *error_message);

// color.c
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

// flooding_algorithm.c
int check_map_validity(char **map);

// get_color.c
int get_color(cub3d_t *cub3d, int element, char **info);

// get_elements.c
int all_elements_found(int *element_found);
void remove_newline(char *line);
int get_elements(cub3d_t *cub3d, int fd);

// get_map.c
int read_cub_file(cub3d_t *cub3d, char *map_path);

// get_texture.c
int get_texture(cub3d_t *cub3d, int element, char **info);

// extra.c
void print_info(cub3d_t *cub3d);
void print_array(char **array, char  *name);
void print_map(char **map);
void test(void);

#endif
