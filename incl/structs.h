#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"

// prototypes
typedef struct map_node_s map_node_t;
typedef struct enemy_path_s enemy_path_t;
typedef struct key_node_s key_node_t;
typedef struct door_pos_s door_pos_t;

//---- TEXTURE -----------------------------------------------------------------

typedef struct texture_s
{
	char	*path;
	int		*img;
	int		width;
	int		height;
}			texture_t;

//---- VECTORS -----------------------------------------------------------------

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

//---- PLAYER ------------------------------------------------------------------

typedef struct player_s
{
	dvector_t	pos;
	dvector_t	new_pos;
	dvector_t	dir;
	double		angle;
	double		movement_angle;
	int			is_walking;
	int			is_strafing;
}				player_t;

typedef struct s_enemy
{
	dvector_t		pos;
	dvector_t		target;
	dvector_t		dir;
	double			angle;
	double			dir_player;
	int				is_walking;
	int				is_spinning;
	enemy_path_t	*path;
}	t_enemy;

typedef struct map_node_s
{
	char		*line;
	map_node_t	*next;
}			map_node_t;

typedef struct enemy_path_s
{
	dvector_t		path;
	enemy_path_t	*next;
	enemy_path_t	*prev;
}		enemy_path_t;

typedef struct keypress_s
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	fisheye;
	int	left;
	int	right;
	int	up;
	int	down;
	int	mouse_left;
	int	mouse_right;
}			keypress_t;

//---- DOORS  ------------------------------------------------------------------

# define NUM_DOORS_MAX 4

typedef struct key_node_s
{
	vector_t	pos;
	int			collected;
	key_node_t		*next;
}				key_node_t;

typedef struct key_group_s
{
	int			index;
	key_node_t	*keys;
}				key_group_t;

typedef struct door_pos_s
{
	vector_t	pos;
	door_pos_t	*next;
}				door_pos_t;

typedef struct door_group_s
{
	int			index; // unnecessary?
	door_pos_t	*door_positions;
	int			group_size;
	int			num_keys_left; // is it needed?
}				door_group_t;

//---- MINIMAP -----------------------------------------------------------------

typedef struct minimap_s
{
	mlx_image_t	*img;
	vector_t	pos;
	dvector_t	player_pos;
	int			width;
	int			height;
	int			size_percentage;
	int			tile_size;
	int			color;			// DON'T THINK WE NEED THIS...
	int			color_player;
	int			color_playerdir;
	int			color_fov;
	int			color_floor;
	int			color_door;
	int			color_wall;
	int			color_empty;
	int			transparency;
}			minimap_t;

//---- RAY ---------------------------------------------------------------------

typedef struct ray_s
{
	dvector_t	end;
	double		angle;
	double		length;
	char		target;
	int			wall;
}				ray_t;

//---- RECTANGLE ---------------------------------------------------------------

typedef struct rectangle_s
{
	vector_t	pos;
	int			width;
	int			height;
	int			color;
}				rectangle_t;

//---- SLIDER ------------------------------------------------------------------

typedef struct slider_s
{
	mlx_image_t	*img;
	vector_t	pos;
	int			width;
	int			height;
	int			color;
	int			background_color;
	int			value;
	int			max_value;
}				slider_t;

//---- BOX ---------------------------------------------------------------------

# define BOX_ON_COLOR GREEN
# define BOX_OFF_COLOR BLACK
# define BOX_HOVER_ON_COLOR LAWN_GREEN
# define BOX_HOVER_OFF_COLOR GRAY
# define BOX_BORDER_COLOR GOLD

# define OFF 0
# define ON 1

typedef struct box_s
{
	mlx_image_t	*text;
	vector_t	pos;
	int			size;
	int			background_color;
	int			border_width;
	int			border_color;
	int			value;
	int			state;
}				box_t;

//---- PAUSE MENU --------------------------------------------------------------

# define PAUSE_MENU_BACKGROUND_COLOR BLACK
# define PAUSE_MENU_TRANSPARENCY 1
# define PAUSE_MENU_SETTINGS_RECT_COLOR 0x2F1E45FF

typedef struct pause_menu_s
{
	mlx_image_t	*img;
	int			background_color;
	mlx_image_t	*text_title;
	mlx_image_t	*text_fps;
	mlx_image_t	*text_fisheye;
	mlx_image_t	*text_mouse;
	rectangle_t	rect_title;
	int			pos_x_rect_title;
	int			pos_y_rect_title;
	int			pos_col_text;
	int			pos_col_box_1;
	int			pos_col_box_2;
	int			pos_col_box_3;
	int			pos_col_box_4;
	int			pos_col_box_5;
	int			pos_text_row_1;
	int			pos_text_row_2;
	int			pos_text_row_3;
	int			pos_row_1;
	int			pos_row_2;
	int			pos_row_3;
	box_t		box_fps[4];
	box_t		box_fisheye[2];
	box_t		box_mouse[2];
}				pause_menu_t;

//---- SETTINGS MENU -----------------------------------------------------------

typedef struct settings_menu_s
{
	mlx_image_t	*img;
	mlx_image_t	*text_settings;
	mlx_image_t	*text_e_difficulty;
	mlx_image_t	*text_minimap_view;
	int			background_color;
}				settings_menu_t;


//---- SETTINGS ----------------------------------------------------------------

enum fps
{
	FPS_15,
	FPS_30,
	FPS_60,
	FPS_120
};

typedef struct settings_s
{
	int		e_difficulty;
	int		minimap_view;
	int 	fps;
	int		fisheye;
	int		mouse;
}			settings_t;


//---- CUB3D -------------------------------------------------------------------

enum state
{
	STATE_START,
	STATE_SETTINGS,
	STATE_GAME,
	STATE_PAUSE
};

typedef struct cub3d_s
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	vector_t		mouse;
	vector_t		mouse_set_pos;
	int				on_minimap;
	vector_t		orig_minimap_pos;
	keypress_t		keys;
	player_t		player;
	double			fov;
	vector_t		starting_pos;
	char			starting_dir;
	minimap_t		minimap;
	map_node_t		*map_list;
	int				nodes;
	char			**map;
	int				map_rows;
	int				map_columns;
	texture_t		texture[4];
	int				floor_color;
	int				ceiling_color;
	int				element_found[6];
	ray_t			*rays;
	int				state;
	pause_menu_t	pause_menu;
	int				prev;
	int				fisheye;
	int				num_enemies;
	settings_t		settings;
	t_enemy			*enemy;
	door_group_t	door_groups[NUM_DOORS_MAX];
	key_group_t		key_groups[NUM_DOORS_MAX];
}					cub3d_t;


#endif