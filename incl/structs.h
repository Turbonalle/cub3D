/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:35:53 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:03:33 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"

// prototypes
typedef struct map_node_s	t_map_node;
typedef struct key_node_s	t_key_node;
typedef struct door_pos_s	t_door_pos;

//---- VECTORS -----------------------------------------------------------------

typedef struct vector_s
{
	int	x;
	int	y;
}		t_vector;

typedef struct t_dvector
{
	double	x;
	double	y;
}			t_dvector;

typedef struct t_range
{
	double	start;
	double	end;
}			t_range;

typedef struct uvector_s
{
	uint32_t	col;
	uint32_t	row;
}				t_uvector;

typedef struct four_vector_s
{
	int	e;
	int	k;
	int	d;
	int	z;
}		t_four_vector;

//---- TEXTURE -----------------------------------------------------------------

typedef struct texture_s
{
	char			*path;
	mlx_texture_t	*texture;
}					t_texture;

//---- PNG ---------------------------------------------------------------------

typedef struct png_s
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	t_vector		pos;
	int				width;
	int				height;
}					t_png;

//---- PLAYER ------------------------------------------------------------------

# define DISTRACTION_THROW_DISTANCE 5

typedef struct player_s
{
	t_dvector	pos;
	t_dvector	new_pos;
	t_dvector	dir;
	int			thrown;
	double		angle;
	double		movement_angle;
	double		hit_timestamp;
	int			health;
	int			mushroom_count;
	int			is_walking;
	int			is_strafing;
	int			num_completed;
	int			is_dirty_cheater;
}				t_player;

enum e_enemy_state
{
	IDLE,
	WALKING,
	HUNTING
};

typedef struct s_enemy
{
	t_dvector		pos;
	t_dvector		target;
	t_dvector		dir;
	t_dvector		minimap_pos;
	t_vector		pos_screen;
	double			freeze_start;
	double			angle;
	double			angle_start;
	double			dir_player;
	int				is_walking;
	int				is_spinning;
	int				is_eating;
	double			dist_to_player;
	int				state;
	int				visible;
	int				is_hunting;
	mlx_image_t		*img_curr_frame;
}					t_enemy;

typedef struct keypress_s
{
	int	q;
	int	w;
	int	e;
	int	r;
	int	t;
	int	y;
	int	u;
	int	i;
	int	o;
	int	p;
	int	a;
	int	s;
	int	d;
	int	f;
	int	g;
	int	h;
	int	j;
	int	k;
	int	l;
	int	z;
	int	x;
	int	c;
	int	v;
	int	b;
	int	n;
	int	m;
	int	space;
	int	backspace;
	int	shift;
	int	enter;
	int	escape;
	int	left;
	int	right;
	int	up;
	int	down;
	int	mouse_left;
	int	mouse_right;
}		t_keypress;

//---- DOORS  ------------------------------------------------------------------

# define NUM_DOORS_MAX 4

typedef struct key_node_s
{
	t_dvector	pos;
	t_vector	pos_screen;
	double		dist_to_player;
	int			visible;
	int			collected;
	mlx_image_t	*img_curr_frame;
	t_key_node	*next;
}				t_key_node;

typedef struct key_group_s
{
	int				index;
	int				num_keys_total;
	t_key_node		*keys;
	mlx_image_t		*img_key_icon;
	mlx_image_t		*img_text_key_count;
	mlx_texture_t	**textures_frames; // TODO: delete textures in the end
	mlx_texture_t	*texture_key_icon;
	char			*texture_dir;
	int				prev_frame_index;
	int				curr_frame_index;
	t_vector		key_icon_coords;
}					t_key_group;

typedef struct door_pos_s
{
	t_vector	pos;
	t_door_pos	*next;
}				t_door_pos;

typedef struct door_group_s
{
	int			index;
	t_door_pos	*door_positions;
	int			num_keys_left;
}				t_door_group;

//---- MINIMAP -----------------------------------------------------------------

typedef struct minimap_s
{
	mlx_image_t	*img;
	t_vector	pos;
	t_dvector	player_pos;
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
	int			color_shroom;
	int			color_enemy;
	int			color_key_1;
	int			color_key_2;
	int			color_key_3;
	int			color_key_4;
	int			transparency;
}				t_minimap;

//---- RAY ---------------------------------------------------------------------

typedef struct ray_s
{
	t_dvector	end;
	double		angle;
	double		length;
	char		target;
	int			wall;
	int			door_dir;
}				t_ray;

//---- TRIANGLE ----------------------------------------------------------------

# define ENEMY_CURSOR_COLOR RED_LIGHT
# define ENEMY_CURSOR_MAX_HEIGHT 50
# define ENEMY_CURSOR_MIN_HEIGHT 10
# define ENEMY_CURSOR_MARGIN 60

typedef struct triangle_s
{
	int			height;
	int			base;
	t_dvector	a;
	t_dvector	b;
	t_dvector	c;
}				t_triangle;

//---- RECTANGLE ---------------------------------------------------------------

typedef struct rectangle_s
{
	t_vector	pos;
	int			width;
	int			height;
	int			color;
}				t_rectangle;

//---- SLIDER ------------------------------------------------------------------

typedef struct slider_s
{
	t_vector	pos;
	int			width;
	int			height;
	int			length;
	int			color;
	int			background_color;
	int			max_value;
	int			min_value;
	double		value;
	int			marker_min_pos;
	int			marker_max_pos;
	mlx_image_t	*marker;
	t_vector	marker_pos;
	int			marker_orig_pos;
	int			on_marker;
}				t_slider;

//---- BOX ---------------------------------------------------------------------

# define BOX_ON_COLOR GREEN
# define BOX_OFF_COLOR BLACK
# define BOX_HOVER_ON_COLOR GREEN_LIGHT
# define BOX_HOVER_OFF_COLOR GRAY_DARK
# define BOX_BORDER_COLOR YELLOW_PALE

# define OFF 0
# define ON 1

typedef struct box_s
{
	mlx_image_t	*text;
	t_vector	pos;
	int			size;
	int			background_color;
	int			border_width;
	int			border_color;
	int			value;
	int			state;
}				t_box;

//---- BUTTON ------------------------------------------------------------------

# define BUTTON_CLICKED_COLOR GREEN
# define BUTTON_HOVER_COLOR GRAY_MED
# define BUTTON_COLOR GRAY_DARK
# define BUTTON_BORDER_COLOR YELLOW_PALE
# define BUTTON_BORDER_THICKNESS 2

typedef struct button_s
{
	mlx_image_t	*text;
	t_vector	pos;
	int			width;
	int			height;
	int			background_color;
	int			border_width;
	int			border_color;
	int			state;
}				t_button;

//---- PAUSE MENU --------------------------------------------------------------

# define PAUSE_MENU_BACKGROUND_COLOR BLACK
# define PAUSE_MENU_TRANSPARENCY 1
# define PAUSE_MENU_SETTINGS_RECT_COLOR 0x2F1E45FF
# define PAUSE_PNG "./assets/textures/menu/pause.png"
# define SLIDER_LINE_COLOR WHITE
# define SLIDER_LINE_WIDTH 8
# define SLIDER_MARKER_COLOR RED_LIGHT
# define SLIDER_MARKER_BORDER_COLOR BLACK
# define SLIDER_MARKER_BORDER_THICKNESS 2
# define SLIDER_MARKER_WIDTH 30
# define SLIDER_MARKER_HEIGHT 40

typedef struct pause_menu_s
{
	mlx_image_t	*bg;
	mlx_image_t	*menu;
	t_vector	menu_pos;
	t_png		title;
	mlx_image_t	*text_title;
	mlx_image_t	*text_fps;
	mlx_image_t	*text_fisheye;
	mlx_image_t	*text_mouse;
	mlx_image_t	*text_mouse_sensitivity;
	int			pos_col_text;
	int			pos_col_box_1;
	int			pos_col_box_2;
	int			pos_col_box_3;
	int			pos_col_box_4;
	int			pos_col_box_5;
	int			pos_text_row_1;
	int			pos_text_row_2;
	int			pos_text_row_3;
	int			pos_text_row_4;
	int			pos_row_1;
	int			pos_row_2;
	int			pos_row_3;
	int			pos_row_4;
	t_box		box_fps[4];
	t_box		box_fisheye[2];
	t_box		box_mouse[2];
	t_slider	sensitivity_slider;
}			t_pause_menu;

//---- START MENU --------------------------------------------------------------

# define MENU_BACKGROUND_COLOR GRAY_DARK
# define MENU_BORDER_TOP_COLOR GREEN
# define MENU_BORDER_BOTTOM_COLOR BURGUNDY_DARK
# define MENU_BORDER_LEFT_COLOR TURQUOISE_LIGHT
# define MENU_BORDER_RIGHT_COLOR RED_LIGHT
# define MENU_BORDER_THICKNESS 30
# define BACK_PNG "./assets/textures/menu/back_normal.png"
# define BACK_HOVER_PNG "./assets/textures/menu/back_hover.png"
# define ARROW_PNG "./assets/textures/menu/arrow_pick.png"

# define START_TITLE_PNG "./assets/textures/logox2.png"
# define START_START_PNG "./assets/textures/menu/start_normal.png"
# define START_START_HOVER_PNG "./assets/textures/menu/start_hover.png"
# define START_LEVEL_PNG "./assets/textures/menu/levels_normal.png"
# define START_LEVEL_HOVER_PNG "./assets/textures/menu/levels_hover.png"
# define START_EXIT_PNG "./assets/textures/menu/exit_normal.png"
# define START_EXIT_HOVER_PNG "./assets/textures/menu/exit_hover.png"

typedef struct start_menu_s
{
	mlx_image_t	*img;
	t_png		title;
	t_png		exit;
	t_png		start;
	t_png		level;
	t_png		exit_hover;
	t_png		start_hover;
	t_png		level_hover;
	t_png		arrow_exit;
	t_png		arrow_start;
	t_png		arrow_level;
}				t_start_menu;

//---- LEVEL MENU --------------------------------------------------------------

# define LEVEL_TITLE_PNG "./assets/textures/menu/level_title.png"
# define LEADERBOARD_PNG "./assets/textures/menu/leaderboard_normal.png"
# define LEADERBOARD_HOVER_PNG "./assets/textures/menu/leaderboard_hover.png"
# define NUM_1_PNG "./assets/textures/level_numbers/1.png"
# define NUM_2_PNG "./assets/textures/level_numbers/2.png"
# define NUM_3_PNG "./assets/textures/level_numbers/3.png"
# define NUM_4_PNG "./assets/textures/level_numbers/4.png"
# define NUM_5_PNG "./assets/textures/level_numbers/5.png"
# define NUM_6_PNG "./assets/textures/level_numbers/6.png"
# define NUM_7_PNG "./assets/textures/level_numbers/7.png"
# define NUM_8_PNG "./assets/textures/level_numbers/8.png"
# define MINILEVEL_BORDER_COLOR YELLOW_PALE
# define MINILEVEL_BG_COLOR BLACK
# define MINILEVEL_RECT_COLOR RED_LIGHT
# define MINILEVEL_BORDER_THICKNESS 10
# define MINILEVEL_MARGIN 10
# define PREVIEW_WALL_COLOR GRAY_VERY_DARK
# define PREVIEW_FLOOR_COLOR GRAY_DARK

//---- LEADERBOARD MENU --------------------------------------------------------

# define LEADERBOARD_LEVEL_BACKGROUND_COLOR BLACK

typedef struct minilevel_s
{
	mlx_image_t	*img;
	t_vector	pos;
	t_png		number;
	t_rectangle	number_rect;
	int			size;
	mlx_image_t	*border;
	t_vector	preview_pos;
	int			width;
	int			height;
	int			square_size;
}				t_minilevel;

typedef struct level_menu_s
{
	mlx_image_t	*img;
	t_png		title;
	t_png		back;
	t_png		leaderboard;
	t_png		back_hover;
	t_png		leaderboard_hover;
	t_minilevel	minilevels[LEVELS];
}				t_level_menu;

//---- LEADERBOARD -------------------------------------------------------------

# define LEADERBOARD_TITLE_PNG "./assets/textures/menu/leaderboard_title.png"
# define N_ENTRIES 3

typedef struct leaderboard_s
{
	mlx_image_t	*img;
	t_png		title;
	t_png		back;
	t_png		back_hover;
	int			n_entries;
	t_rectangle	rect_level[LEVELS];
	mlx_image_t	*text_level[LEVELS];
}				t_leaderboard;

//---- NAME MENU ---------------------------------------------------------------

# define TOP3_PNG "./assets/textures/menu/top3.png"
# define MAX_NAME_LENGTH 12
# define ALPHABET "abcdefghijklmnopqrstuvwxyz "
# define ALPHABET_LENGTH 26
# define NAME_BOX_GAP 5

enum e_letters
{
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z
};

typedef struct letter_box_s
{
	char		letter[2];
	t_vector	pos;
	int			width;
	int			height;
	int			background_color;
	int			border_width;
	int			border_color;
	int			value;
	int			state;
}				t_letter_box;

typedef struct name_menu_s
{
	mlx_image_t		*img;
	t_png			title_win;
	t_png			title_top3;
	t_png			back;
	t_png			back_hover;
	t_png			timer;
	char			time_str[9];
	mlx_image_t		*text_time;
	t_rectangle		rect_title;
	t_rectangle		rect_input;
	int				current;
	char			letter;
	mlx_image_t		*letters_img[ALPHABET_LENGTH];
	char			letter_str[ALPHABET_LENGTH + 1][2];
	t_letter_box	box[MAX_NAME_LENGTH];
	char			name[MAX_NAME_LENGTH + 1];
	int				letter_index[MAX_NAME_LENGTH];
	int				changed;
}				t_name_menu;

//---- GAMEOVER MENU -----------------------------------------------------------

# define GAMEOVER_GAMEOVER_PNG "./assets/textures/menu/game_over.png"
# define GAMEOVER_WIN_PNG "./assets/textures/menu/you_won.png"
# define GAMEOVER_EXIT_PNG "./assets/textures/menu/exit_normal.png"
# define GAMEOVER_EXIT_HOVER_PNG "./assets/textures/menu/exit_hover.png"
# define GAMEOVER_RESTART_PNG "./assets/textures/menu/try_again_normal.png"
# define GAMEOVER_RESTART_HOVER_PNG "./assets/textures/menu/try_again_hover.png"
# define TIMER_PNG "./assets/textures/menu/timer.png"

typedef struct gameover_menu_s
{
	mlx_image_t	*img;
	t_png		title_win;
	t_png		title_gameover;
	t_png		back;	
	t_png		back_hover;
	t_png		restart;
	t_png		restart_hover;
	t_png		arrow_back;
	t_png		arrow_restart;
	t_png		timer;
	char		time_str[9];
	mlx_image_t	*text_time;
}				t_gameover_menu;

//---- SETTINGS ----------------------------------------------------------------

enum e_fps
{
	FPS_15,
	FPS_30,
	FPS_60,
	FPS_120
};

typedef struct settings_s
{
	int		e_speed;
	int		e_behaviour;
	int		fps;
	int		fisheye;
	int		mouse;
	double	mouse_sensitivity;
}			t_settings;

//---- TIMER -------------------------------------------------------------------

typedef struct gametimer_s
{
	mlx_image_t	*img_time;
	char		*text_time;
	t_vector	pos;
	double		start_timestamp;
	double		pause_timestamp;
	double		run_time;
	double		delta_time;
}				t_gametimer;

//---- MAPS --------------------------------------------------------------------

typedef struct map_node_s
{
	char		*line;
	t_map_node	*next;
}				t_map_node;

typedef struct record_s
{
	int				time;
	char			*name;
	char			time_str[9];
	mlx_image_t		*text_name;
	mlx_image_t		*text_time;
	struct record_s	*next;
}				t_record;

typedef struct distract_s
{
	int			collected;
	int			visible;
	int			thrown;
	t_dvector	pos;
	t_vector	pos_screen;
	double		dist_to_player;
	mlx_image_t	*img_distraction;
}				t_distract;

typedef struct level_s
{
	char			**map;
	char			**backup;
	t_vector		starting_pos;
	char			starting_dir;
	int				map_rows;
	int				map_columns;
	t_map_node		*map_list;
	int				nodes;
	t_texture		texture[4];
	t_texture		heart;
	t_texture		heart_half;
	t_texture		heart_empty;
	int				floor_color;
	int				ceiling_color;
	int				element_found[6];
	t_door_group	door_groups[NUM_DOORS_MAX];
	t_key_group		key_groups[NUM_DOORS_MAX];
	t_distract		*distractions;
	int				num_distractions;
	t_dvector		distraction;
	double			distraction_amount;
	t_record		*records;
	mlx_image_t		*heart_img;
	mlx_image_t		*heart_half_img;
	mlx_image_t		*heart_empty_img;
}			t_level;

//---- HALO --------------------------------------------------------------------

typedef struct halo_s
{
	mlx_image_t	*img;
	int			active;
	int			color;
	double		timestamp;
}				t_halo;

//---- HEARTS ------------------------------------------------------------------

# define HEART_FULL_PNG "./assets/textures/heart/full.png"
# define HEART_EMPTY_PNG "./assets/textures/heart/empty.png"
# define HEARTS 3
# define HEART_GAP 10

typedef struct heart_s
{
	t_png		full;
	t_png		empty;
}				t_heart;

//---- SHROOM ------------------------------------------------------------------

typedef struct shroom_s
{
	t_png		shroom;
	mlx_image_t	*text;
}			t_shroom;

//---- FISHEYE -----------------------------------------------------------------

typedef struct t_fisheye
{
	double		perp_dist;
	t_dvector	orto_dir;
	t_dvector	ray;
	double		proj_len;
	t_dvector	ray_proj;
	t_dvector	ray_perp;
	double		view_fill_dist;
	double		window_aspect_ratio;
}				t_fisheye;

//---- FRUSTUM -----------------------------------------------------------------

# define FRUSTUM_FAR 100
# define FRUSTUM_NEAR 1.777771

typedef struct frustum_s
{
	double		half_fov;
	t_dvector	far_left;
	t_dvector	far_right;
	t_dvector	near_left;
	t_dvector	near_right;
	t_dvector	left;
	t_dvector	right;
}				t_frustum;

//---- RAYCAST -----------------------------------------------------------------

typedef struct raycast_s
{
	t_dvector	v_ray_step_size;
	t_dvector	v_ray_1d_length;
	t_vector	v_map_check;
	t_vector	v_step;
	double		dist;
	double		delta;
}				t_raycast;

//---- CUB3D -------------------------------------------------------------------

# define INTRO_PNG "./assets/textures/menu/intro.png"

enum e_state
{
	STATE_START,
	STATE_LEVEL,
	STATE_LEADERBOARD,
	STATE_INTRO,
	STATE_GAME,
	STATE_PAUSE,
	STATE_ENTERNAME,
	STATE_GAMEOVER
};

# define FLOOR_PNG "./assets/textures/surfaces/floor.png"

# define NUM_ENEMY_DIRECTIONS 6
# define NUM_DOOR_TEXTURES 5

enum e_enemy_direction
{
	AWAY,
	RIGHT,
	RIGHT_45,
	STRAIGHT,
	LEFT_45,
	LEFT
};

typedef struct cub3d_s
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	double			start_timestamp;
	double			frame_time;
	double			frame_start_timestamp;
	double			run_time;
	double			delta_time;
	double			pause_timestamp;
	int				time_finished;
	t_vector		mouse;
	t_vector		mouse_set_pos;
	int				on_minimap;
	t_vector		orig_minimap_pos;
	t_keypress		keys;
	t_player		player;
	double			fov;
	t_minimap		minimap;
	t_halo			halo;
	t_heart			hearts[HEARTS];
	t_ray			*rays;
	int				state;
	int				prev;
	int				num_enemies;
	t_start_menu	start_menu;
	t_level_menu	level_menu;
	t_leaderboard	leaderboard;
	t_pause_menu	pause_menu;
	t_name_menu		name_menu;
	t_gameover_menu	gameover_menu;
	t_vector		back_button_pos;
	t_settings		settings;
	t_png			intro;
	int				intro_watched;
	t_gametimer		timer;
	int				n_levels;
	t_level			*levels;
	t_level			*level;
	t_enemy			*enemy;
	mlx_texture_t	*frames_idle[NUM_ENEMY_DIRECTIONS][NUM_FRAMES_ENEMY_IDLE];
	mlx_texture_t	*frames_walking[NUM_ENEMY_DIRECTIONS][NUM_FRAMES_WALKING];
	mlx_texture_t	*frames_hunting[NUM_ENEMY_DIRECTIONS][NUM_FRAMES_HUNTING];
	mlx_texture_t	*distraction_texture;
	mlx_texture_t	*distraction_thrown_texture;
	t_shroom		*shroom;
	int				curr_frame_index_hunting;
	int				prev_frame_index_hunting;
	int				curr_frame_index_walking;
	int				prev_frame_index_walking;
	int				curr_frame_index_idle;
	int				prev_frame_index_idle;
	double			prev_frame_update_timestamp;
	int				speedrun;
	int				draw_floor;
	t_texture		floor;
	t_texture		stars[NUM_FRAMES_STARS];
	t_texture		door[NUM_DOOR_TEXTURES];
	t_fisheye		fisheye;
	t_frustum		frustum;
	t_raycast		raycast;
}					t_cub3d;

#endif