#ifndef CUB3D_H
# define CUB3D_H
# include "colors.h"
# include "terminal_colors.h"
# include "MLX42/MLX42.h"
# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <math.h>
# include "consts.h"
# include "structs.h"

//---- COLOR -------------------------------------------------------------------

// get_color.c
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);

// set_color.c
int		set_rgba(int r, int g, int b, int a);
int		set_r(int rgba, int r);
int		set_g(int rgba, int g);
int		set_b(int rgba, int b);
int		set_a(int rgba, int a);

// transparency.c
int		set_transparency(int color, int transparency);

//---- PARSING -----------------------------------------------------------------

// get_color.c
int		get_color(cub3d_t *cub3d, int element, char **info);

// get_elements.c
int		all_elements_found(int *element_found);
void	remove_newline(char *line);
int		get_elements(cub3d_t *cub3d, int fd);

// get_map.c
int		read_cub_file(cub3d_t *cub3d, char *map_path);

// get_texture.c
int		get_texture(cub3d_t *cub3d, int element, char **info);

// flooding_algorithm.c
int		check_map_validity(char **map);


//---- DRAWING -----------------------------------------------------------------

void draw_world(cub3d_t *cub3d);
void draw_vertical_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);
void	draw_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);


//---- INIT --------------------------------------------------------------------

// init_cub3d.c
int		count_minimap_tilesize(cub3d_t *cub3d, int size_percentage);
int		init_rays(cub3d_t *cub3d);
int		init_cub3d(cub3d_t *cub3d);

// init_pause_menu.c
void	init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);

// init_start_menu.c
void	init_start_menu(cub3d_t *cub3d, start_menu_t *menu);


//---- START MENU --------------------------------------------------------------

// start_menu.c
void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu);

// draw_start_menu.c
void	draw_button(mlx_image_t *img, button_t *button);
void	draw_start_menu_background(cub3d_t *cub3d, start_menu_t *menu);
void	draw_start_menu(cub3d_t *cub3d, start_menu_t *menu);


//---- PAUSE MENU --------------------------------------------------------------

void	delete_pause_menu(cub3d_t *cub3d);

// pause_text.c
void	add_title_text(cub3d_t *cub3d, pause_menu_t *menu);
void	add_category_text(cub3d_t *cub3d, pause_menu_t *menu);
void	add_checkbox_text(cub3d_t *cub3d, pause_menu_t *menu);

// pause_menu.c
void	update_settings(cub3d_t *cub3d, pause_menu_t *menu);
void	update_pause_settings(cub3d_t *cub3d, pause_menu_t *menu);
void	update_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);
void	draw_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);


// center.c
void	center(mlx_image_t *img);
void	center_vertically(mlx_image_t *img);
void	center_horizontally(mlx_image_t *img);

// hover.c
int		hover_button(cub3d_t *cub3d, button_t *button);
int		hover_rectangle(cub3d_t *cub3d, rectangle_t *rect);
int		hover_box(cub3d_t *cub3d, box_t *box);
int		hover_any_box(cub3d_t *cub3d, pause_menu_t *menu);


//---- DRAW --------------------------------------------------------------------

void	draw_rectangle(mlx_image_t *img, rectangle_t *rect);
void	draw_checkbox(cub3d_t *cub3d, box_t *box);
void	draw_hovered_checkbox(cub3d_t *cub3d, box_t *box);


//---- MATH --------------------------------------------------------------------

// math.c
double	within_360(double degree);
double	within_two_pi(double radians);
double	to_radians(double degrees);
double	dist_between(vector_t a, dvector_t b);

// dda.c
int		find_end_point(cub3d_t *cub3d, player_t *player, double radians, dvector_t *end);


//---- CORE --------------------------------------------------------------------

// start_game.c
void	start_game(cub3d_t *cub3d);



//---- PLAYER ------------------------------------------------------------------

// collision.c
void	collision_checker(cub3d_t *cub3d);

// player_movement.c
void	player_movement(cub3d_t *cub3d);

// fov.c
void	increase_fov(cub3d_t *cub3d);
void	decrease_fov(cub3d_t *cub3d);

//---- DOORS -------------------------------------------------------------------

int	init_doors_and_keys(cub3d_t *cub3d);

//---- INPUT -------------------------------------------------------------------

// handle_close.c
void	handle_close_window(void *param);
void	handle_escape_key(mlx_key_data_t *keydata, mlx_t *mlx);

// handle_keys.c
void	get_input(mlx_key_data_t keydata, void *param);

// handle_mouse.c
void	hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param);
void	hook_mouse_scroll(double xdelta, double ydelta, void *param);



//---- MINIMAP -----------------------------------------------------------------

// minimap.c
void	move_minimap(cub3d_t *cub3d);
void	update_minimap(cub3d_t *cub3d);
void	update_minimap_player_pos(cub3d_t *cub3d);
void	minimap(cub3d_t *cub3d);

// minimap_draw_base.c
void	draw_square(cub3d_t *cub3d, int x, int y, int size, int color);
void	draw_minimap(cub3d_t *cub3d);
void	draw_minimap_border(cub3d_t *cub3d);

// minimap_draw_player.c
void	draw_minimap_player(cub3d_t *cub3d);
void	draw_minimap_playerdir(cub3d_t *cub3d);
void	draw_fov(cub3d_t *cub3d);

// minimap_zoom.c
int		hover_minimap(cub3d_t *cub3d);
void	zoom_in_minimap(cub3d_t *cub3d);
void	zoom_out_minimap(cub3d_t *cub3d);



//---- RAYCASTING --------------------------------------------------------------

// raycasting.c
void	raycasting(cub3d_t *cub3d);



//---- UTILS -------------------------------------------------------------------

// memory_utils.c
void	free_info(char **info);
void	free_cub3d(cub3d_t *cub3d);
void	free_list(map_node_t *node);

// error_utils.c
int		err(char *error_message);

//---- EXTRA (REMOVE THESE BEFORE EVALUATION) ----------------------------------

// extra.c
void	print_info(cub3d_t *cub3d);
void	print_array(char **array, char *name);
void	print_map(char **map);
void	test(void);
void	print_settings(cub3d_t *cub3d);


int		init_enemy(cub3d_t *cub3d);
void	enemy_vision(cub3d_t *cub3d);
#endif
