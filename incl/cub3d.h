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

void	count_enemies(cub3d_t *cub3d);
void	set_initial_direction(cub3d_t *cub3d);
int		count_minimap_tilesize(cub3d_t *cub3d, int size_percentage);
void	init_minimap(cub3d_t *cub3d);

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
// int		get_color(cub3d_t *cub3d, int element, char **info);
int		get_color(level_t *level, int element, char **info);

// get_elements.c
int		all_elements_found(int *element_found);
void	remove_newline(char *line);
// int		get_elements(cub3d_t *cub3d, int fd);
int		get_elements(level_t *level, int fd);

// get_map.c
// int		read_cub_file(cub3d_t *cub3d, char *map_path);
int		read_cub_file(level_t *level, char *map_path);

// get_texture.c
// int		get_texture(cub3d_t *cub3d, int element, char **info);
int		get_texture(level_t *level, int element, char **info);

// flooding_algorithm.c
int		check_map_validity(char **map);


//---- DRAWING -----------------------------------------------------------------

void	draw_world(cub3d_t *cub3d);
void	draw_vertical_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);
void	draw_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);


//---- INIT --------------------------------------------------------------------

// init_cub3d.c
int		count_minimap_tilesize(cub3d_t *cub3d, int size_percentage);
int		init_rays(cub3d_t *cub3d);
int		init_cub3d(cub3d_t *cub3d);

// init_level_menu.c
void	init_level_menu(cub3d_t *cub3d, level_menu_t *menu);

// init_name_menu.c
void	init_name_menu(cub3d_t *cub3d, name_menu_t *menu);

// init_pause_menu.c
void	init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);

// init_start_menu.c
void	init_start_menu(cub3d_t *cub3d, start_menu_t *menu);

// init_leaderboard.c
int		init_leaderboard(cub3d_t *cub3d, leaderboard_t *board);

//---- START MENU --------------------------------------------------------------

// delete_menu.c
void	delete_menus(cub3d_t *cub3d);
void	delete_start_menu(cub3d_t *cub3d, start_menu_t *menu);
void	delete_level_menu(cub3d_t *cub3d, level_menu_t *menu);
void	delete_leaderboard(cub3d_t *cub3d, leaderboard_t *board);
void	delete_name_menu(cub3d_t *cub3d, name_menu_t *menu);

// disable_menu.c
void	disable_name_menu(name_menu_t *menu);

void	draw_menu_background(mlx_image_t *img, int color);
void	draw_button(mlx_image_t *img, button_t *button);

// draw_level_menu.c
void	draw_level_menu(cub3d_t *cub3d, level_menu_t *menu);

// update_level_menu.c
void	update_level_menu(cub3d_t *cub3d, level_menu_t *menu);

// draw_leaderboard.c
int		draw_leaderboard(cub3d_t *cub3d, leaderboard_t *board);

// name menu
int		draw_name_menu(cub3d_t *cub3d, name_menu_t *menu);
void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu);

// update_leaderboard.c
void	update_leaderboard(cub3d_t *cub3d, leaderboard_t *board);

// draw_start_menu.c
void	draw_button(mlx_image_t *img, button_t *button);
void	draw_start_menu_background(cub3d_t *cub3d, start_menu_t *menu);
void	draw_start_menu(cub3d_t *cub3d, start_menu_t *menu);

// update_start_menu.c
void	get_transition_color(cub3d_t *cub3d, int *color);
void	check_button_hover(cub3d_t *cub3d, start_menu_t *menu);
void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu);

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
int		get_door_key_color(cub3d_t *cub3d, int index);


//---- MATH --------------------------------------------------------------------

// math.c
double	within_360(double degree);
double	within_two_pi(double radians);
double	to_radians(double degrees);
double	dist_between(vector_t a, dvector_t b);

// dda.c
int		find_end_point(cub3d_t *cub3d, player_t player, double radians, dvector_t end);
int		all_keys_found(cub3d_t *cub3d, int i);


//---- CORE --------------------------------------------------------------------

// cursor.c
void	handle_cursor(cub3d_t *cub3d);

// game_over.c
void	game_over(cub3d_t *cub3d);

// records.c
int		add_record(record_t **records, int time, char *name, int n_entries);
int		read_records(cub3d_t *cub3d, level_t *levels);

// load_level.c
void	load_level(cub3d_t *cub3d, level_t *level);

// start_game.c
void	start_game(cub3d_t *cub3d);

// time.c
double	elapsed_time(cub3d_t *cub3d);
void	handle_fps(cub3d_t *cub3d);
void	set_fps(double *frame_time, int fps);
void	start_timer(cub3d_t *cub3d);
void	pause_timer(cub3d_t *cub3d);
void	continue_timer(cub3d_t *cub3d);
void	draw_timer(cub3d_t *cub3d);
void	print_timer(cub3d_t *cub3d);


//---- PLAYER ------------------------------------------------------------------

// collision.c
void	collision_checker(cub3d_t *cub3d);
void	item_collected_checker(cub3d_t *cub3d);

// player_movement.c
void	player_movement(cub3d_t *cub3d);

// fov.c
void	increase_fov(cub3d_t *cub3d);
void	decrease_fov(cub3d_t *cub3d);

//---- DOORS -------------------------------------------------------------------

int	get_door_index(char symbol);
int	get_key_index(char symbol);
int	init_doors_and_keys(cub3d_t *cub3d);

//key_counts.c
void draw_key_counts(cub3d_t *cub3d);
void    draw_animated_keys(cub3d_t *cub3d);

//---- INPUT -------------------------------------------------------------------

// handle_close.c
void	handle_close_window(void *param);

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
void	draw_minimap(cub3d_t *cub3d);
void	draw_minimap_border(cub3d_t *cub3d);

// minimap_draw_player.c
void	draw_minimap_player(cub3d_t *cub3d);
void	draw_minimap_playerdir(cub3d_t *cub3d);
void	draw_extras(cub3d_t *cub3d, int row, int column);
void	draw_fov(cub3d_t *cub3d);

// minimap_zoom.c
int		hover_minimap(cub3d_t *cub3d);
void	zoom_in_minimap(cub3d_t *cub3d);
void	zoom_out_minimap(cub3d_t *cub3d);


//---- RAYCASTING --------------------------------------------------------------

// raycasting.c
void	raycasting(cub3d_t *cub3d);


//---- UTILS -------------------------------------------------------------------

// check_utils.c
int		all_alpha(char *str);
int		all_digits(char *str);

// memory_utils.c
void	free_info(char **info);
void	free_cub3d(cub3d_t *cub3d);
void	free_list(map_node_t *node);
void	free_record(record_t *record);
void	free_doors(door_pos_t *head);
void	free_keys(key_node_t *head);

// error_utils.c
int		err(char *error_message);

// drawing_utils.c
void draw_square(mlx_image_t *img, int col, int row, int size, int color);
void mlx_draw_horizontal_line(mlx_image_t *img, int x1, int x2, int y, int color);
void draw_circle(mlx_image_t *img, int col, int row, int radius, int color);

//---- EXTRA (REMOVE THESE BEFORE EVALUATION) ----------------------------------

// extra.c
void	print_level_info(level_t *level);
void	print_array(char **array, char *name);
void	print_map(char **map);
void	test(void);
void	print_settings(cub3d_t *cub3d);
void	print_letter_indexes(name_menu_t *menu, int backspace);


int		init_enemy(cub3d_t *cub3d);
void	enemy_vision(cub3d_t *cub3d);

void	draw_enemies(cub3d_t *cub3d);
#endif
