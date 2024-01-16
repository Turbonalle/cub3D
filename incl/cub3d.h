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
int		init_minimap(cub3d_t *cub3d);

//---- COLOR -------------------------------------------------------------------

uint32_t	get_pixel_color(texture_t texture, vector_t src);

// mix_color.c
int		get_color_mix(int color1, int color2);

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


//---- CORE --------------------------------------------------------------------

// cursor.c
void	handle_cursor(cub3d_t *cub3d);

// game_over.c
void	level_finished(cub3d_t *cub3d);
void	game_over(cub3d_t *cub3d);

// hearts.c
int		load_heart_png(cub3d_t *cub3d);
int		init_full_hearts(cub3d_t *cub3d);
int		init_empty_hearts(cub3d_t *cub3d);
int		set_heart_positions(cub3d_t *cub3d);
int		put_hearts_to_window(cub3d_t *cub3d);
int		init_hearts(cub3d_t *cub3d);
void	delete_full_heart_texture(cub3d_t *cub3d, int i);
void	delete_empty_heart_texture(cub3d_t *cub3d, int i);
void	delete_full_heart_image(cub3d_t *cub3d, int i);
void	delete_empty_heart_image(cub3d_t *cub3d, int i);
void	delete_hearts(cub3d_t *cub3d);
void	disable_hearts(cub3d_t *cub3d);
void	enable_hearts(cub3d_t *cub3d);
void	adjust_hearts(cub3d_t *cub3d);

// records.c
void	create_time_string(char *time_str, int time);
int		add_record(cub3d_t *cub3d, record_t **records, int time, char *name);
int		read_records(cub3d_t *cub3d);
int		get_record_time(char *line, int *time);
int		get_record_name(char *line, char **name);
int		count_records(record_t *records);
record_t	*new_record(int time, char *name);

// set_z_of_all_images.c
void	set_z_of_all_images(cub3d_t *cub3d);

// load_level.c
int		load_level(cub3d_t *cub3d, level_t *level);

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

// halo
int		init_halo(cub3d_t *cub3d);
void	activate_halo(halo_t *halo, int color);
void	handle_halo(halo_t *halo);
void	draw_halo(mlx_image_t *img, halo_t *halo);
double	get_time_fade(halo_t *halo);


//---- PARSE -------------------------------------------------------------------

int		get_color(level_t *level, int element, char **info);
int		all_elements_found(int *element_found);
void	remove_newline(char *line);
int		get_elements(level_t *level, int fd);
int		read_cub_file(level_t *level, char *map_path);
int		create_rectangular_map(level_t *level);
int		get_map(level_t *level, int fd);
int		add_map_line(map_node_t **first_node, char *line);
int		null_textures(level_t *level);
int		read_map(level_t *level, char *map_path);
int		copy_array(char **src, char **dst);
int		free_map_helper(level_t *level, int i);

// get_texture.c
// int		get_texture(cub3d_t *cub3d, int element, char **info);
int		get_texture(level_t *level, int element, char **info);
int		check_map_validity(char **map);
void	zero_map(char **map);

//---- DRAWING -----------------------------------------------------------------

void	draw_world(cub3d_t *cub3d);
void	draw_vertical_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);
void	draw_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);
void	draw_textured_line(cub3d_t *cub3d, dvector_t start, dvector_t end, ray_t ray);
void	draw_textured_line_close(cub3d_t *cub3d, dvector_t start, dvector_t end, ray_t ray);
void	draw_slider(mlx_image_t *img, slider_t *slider);

//---- INIT --------------------------------------------------------------------

// draw_menu_border.c
void	draw_menu_border(mlx_image_t *img);

// init_cub3d.c
int		count_minimap_tilesize(cub3d_t *cub3d, int size_percentage);
int		init_rays(cub3d_t *cub3d);
int		init_cub3d(cub3d_t *cub3d);

// init menus
int		init_level_menu(cub3d_t *cub3d, level_menu_t *menu);
int		init_name_menu(cub3d_t *cub3d, name_menu_t *menu);
void	init_name_values(name_menu_t *menu);
void	draw_letter_box(mlx_image_t *img, letter_box_t *box);
void	init_letter_images(cub3d_t *cub3d, name_menu_t *menu);
void	set_letter_fields(name_menu_t *menu);
int		init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);
int		load_png_pause_menu(pause_menu_t *menu);
int		init_images_pause_menu(mlx_t *mlx, pause_menu_t *menu);
int		init_sensitivity_slider(cub3d_t *cub3d, pause_menu_t *menu);
void	init_checkboxes(pause_menu_t *menu);
void	init_checkbox_states(pause_menu_t *menu);
void	set_checkbox_values(pause_menu_t *menu);
void	init_settings(settings_t *settings);
int		init_start_menu(cub3d_t *cub3d, start_menu_t *menu);
int		load_png_start_menu(start_menu_t *menu);
int		init_images_start_menu(mlx_t *mlx, start_menu_t *menu);
int		init_leaderboard(cub3d_t *cub3d, leaderboard_t *board);
int		init_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu);
int		init_intro(cub3d_t *cub3d);

int		init_stars_textures(cub3d_t *cub3d);
int		init_door_textures(cub3d_t *cub3d);
int		init_doors_and_keys(cub3d_t *cub3d);
void	init_door_values(cub3d_t *cub3d);
int		init_door(cub3d_t *cub3d, int i, int j, int door_group_index);
int		load_door_textures(cub3d_t *cub3d);
int		init_enemy_frames(cub3d_t *cub3d);
int		set_indexes(cub3d_t *cub3d, int i);

int		count_keys(cub3d_t *cub3d, int i);
int		init_key(cub3d_t *cub3d, int i, int j, int key_group_index);
int		free_doors_and_keys(cub3d_t *cub3d);

int		init_shroom(cub3d_t *cub3d);

int		free_prev_start_menu(start_menu_t *menu, int i);
int		free_prev_level_menu(level_menu_t *menu, int i, int j);
int		free_prev_gameover_menu(gameover_menu_t *menu, int i);
int		free_prev_name_menu(name_menu_t *menu, int i);
void	free_textures_before_failed(texture_t *textures, int failed_index);

//---- MENU --------------------------------------------------------------------

// delete_menu.c
void	delete_menus(cub3d_t *cub3d);
void	delete_start_menu(cub3d_t *cub3d, start_menu_t *menu);
void	delete_level_menu(cub3d_t *cub3d, level_menu_t *menu);
void	delete_leaderboard(cub3d_t *cub3d, leaderboard_t *board);
void	delete_name_menu(cub3d_t *cub3d, name_menu_t *menu);

// disable_menu.c

void	draw_background(mlx_image_t *img, int color);
void	draw_button(mlx_image_t *img, button_t *button);

// level menu
void	disable_level_menu(level_menu_t *menu);
void	enable_level_menu(level_menu_t *menu);
void	update_level_menu(cub3d_t *cub3d, level_menu_t *menu);

// leaderboard
void	draw_times(mlx_t *mlx, record_t **records, leaderboard_t *board, int level);
void	draw_names(mlx_t *mlx, record_t **records, leaderboard_t *board, int level);
void	disable_leaderboard(cub3d_t *cub3d, leaderboard_t *board);
void	enable_leaderboard(cub3d_t *cub3d, leaderboard_t *board);
void	update_leaderboard(cub3d_t *cub3d, leaderboard_t *board);

// name menu
void	disable_name_menu(mlx_t *mlx, name_menu_t *menu);
void	enable_name_menu(cub3d_t *cub3d, name_menu_t *menu);
void	update_name_menu(cub3d_t *cub3d, name_menu_t *menu);
int		update_letter(mlx_t *mlx, name_menu_t *menu, int *key, int i);
int		get_letter_first_third(cub3d_t *cub3d, name_menu_t *menu);
int		get_letter_second_third(cub3d_t *cub3d, name_menu_t *menu);
int		get_letter_last_third(cub3d_t *cub3d, name_menu_t *menu);
void	handle_backspace(cub3d_t *cub3d, name_menu_t *menu);
void	remove_record_image_pointers(cub3d_t *cub3d);
void	submit_name(cub3d_t *cub3d, name_menu_t *menu);
int		change_name(cub3d_t *cub3d, name_menu_t *menu);

// start menu
void	disable_start_menu(start_menu_t *menu);
void	enable_start_menu(start_menu_t *menu);
/* void	get_transition_color(cub3d_t *cub3d, int *color); */
void	update_start_menu(cub3d_t *cub3d, start_menu_t *menu);

// gameover menu
void	disable_gameover_menu(mlx_t *mlx, gameover_menu_t *menu);
void	enable_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu, int win);
void	update_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu);

// intro menu
void	disable_intro(cub3d_t *cub3d);
void	enable_intro(cub3d_t *cub3d);

//---- PAUSE MENU --------------------------------------------------------------

int		get_marker_pos(cub3d_t *cub3d);
double	get_sensitivity(cub3d_t *cub3d);

// pause_text.c
void	add_category_text(cub3d_t *cub3d, pause_menu_t *menu);
void	add_checkbox_text(cub3d_t *cub3d, pause_menu_t *menu);

// pause_menu.c
void	update_settings(cub3d_t *cub3d, pause_menu_t *menu);
void	update_pause_settings(cub3d_t *cub3d, pause_menu_t *menu);
void	update_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);
int		pause_menu_helper(cub3d_t *cub3d, pause_menu_t *menu);
void	draw_menu(cub3d_t *cub3d, pause_menu_t *menu);

void	disable_pause_menu(mlx_t *mlx, pause_menu_t *menu);
int		enable_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);

// center.c
void	center(mlx_image_t *img);
void	center_vertically(mlx_image_t *img);
void	center_horizontally(mlx_image_t *img);

// hover.c
int		hover_image(cub3d_t *cub3d, mlx_image_t *img);
int		hover_button(cub3d_t *cub3d, button_t *button);
int		hover_rectangle(cub3d_t *cub3d, rectangle_t *rect);
int		hover_box(cub3d_t *cub3d, box_t *box);
int		hover_any_box(cub3d_t *cub3d, pause_menu_t *menu);

//---- DRAW --------------------------------------------------------------------

void	draw_filled_triangle(mlx_image_t *img, triangle_t *triangle, int color);
// void	draw_triangle(mlx_image_t *img, triangle_t triangle, int color);
void	draw_rectangle(mlx_image_t *img, rectangle_t *rect);
void	draw_checkbox(cub3d_t *cub3d, box_t *box);
void	draw_hovered_checkbox(cub3d_t *cub3d, box_t *box);
int		get_door_key_color(cub3d_t *cub3d, int index);

//---- MATH --------------------------------------------------------------------

// math.c
int		min(int a, int b);
double	within_360(double degree);
double	within_two_pi(double radians);
double	to_radians(double degrees);
double	dist_between(vector_t a, dvector_t b);
double	dist_between_d_vectors(dvector_t a, dvector_t b);
double	lerp(range_t from, range_t to, double value);

// dda.c
int		find_end_point(cub3d_t *cub3d, player_t *player, double radians, dvector_t end);
int		all_keys_found(cub3d_t *cub3d, int i);

//---- PLAYER ------------------------------------------------------------------

// collision.c
void	collision_checker(cub3d_t *cub3d);
void	item_collected_checker(cub3d_t *cub3d);
void	player_is_hit(cub3d_t *cub3d, int i);
void	draw_health(cub3d_t *cub3d);
int		is_locked_door(cub3d_t *cub3d, int y, int x);

// player_movement.c
void	player_movement(cub3d_t *cub3d);
int		is_walking(cub3d_t *cub3d);
int		is_strafing(cub3d_t *cub3d);
void	player_rotation(cub3d_t *cub3d);

// fov.c
void	increase_fov(cub3d_t *cub3d);
void	decrease_fov(cub3d_t *cub3d);

//---- DOORS -------------------------------------------------------------------

int		get_door_index(char symbol);
int		get_key_index(char symbol);

//---- KEY COUNTS --------------------------------------------------------------

//key_count_string_utils.c
void	nullify_strings(char **text1, char **text2, char **text3);
void	free_non_null_strings(char *text1, char *text2, char *text3);

//key_counts.c
int		draw_key_counts(cub3d_t *cub3d);

//---- ANIMATION ---------------------------------------------------------------

// draw_game_entities.c
int	draw_game_entities(cub3d_t *cub3d);

// animation_utils.c
int	get_enemy_dir(t_enemy *enemy);
double	calculate_scale_factor(double dist, double normal_dist);

// assign_z_add_all.c
void	add_all_enemies(t_enemy **enemies, four_vector_t *indexes);
void	add_all_keys(key_node_t **keys, four_vector_t *indexes);
void	add_all_distractions(distraction_t **distractions,
		four_vector_t *indexes);

// assign_z_depth_cases.c
void	case_all_3(t_enemy **enemies, key_node_t **keys,
		distraction_t **distractions, four_vector_t *indexes);
void	case_without_keys(t_enemy **enemies, distraction_t **distractions,
		four_vector_t *indexes);
void	case_without_distractions(t_enemy **enemies, key_node_t **keys,
		four_vector_t *indexes);
void	case_without_enemies(key_node_t **keys, distraction_t **distractions,
		four_vector_t *indexes);

// assign_z_depth_utils.c
int		largest(double i, double j, double k);
void	init_indexes_and_z(cub3d_t *cub3d, four_vector_t *indexes);

// assign_z_depth.c
void	assign_z_depth_ordered_by_distance(cub3d_t *cub3d, t_enemy **enemies,
		key_node_t **keys, distraction_t **distractions);

// draw_distractions.c
void    draw_all_distractions(cub3d_t *cub3d, distraction_t **distractions);

// draw_enemies.c
void	draw_all_enemies(cub3d_t *cub3d, t_enemy **enemies);

// draw_keys.c
void    draw_all_keys(cub3d_t *cub3d);

// draw_utils.c
void	copy_pixel(mlx_image_t *img, uvector_t res, mlx_texture_t *texture,
	uvector_t src);
int		column_visible(cub3d_t *cub3d, double dist_to_player, int ray_index);
int		get_ray_i(double x, mlx_texture_t *texture, double factor, uvector_t res);
void	set_src_coordinates(uvector_t *src, uvector_t res, double factor, mlx_texture_t *texture);
void	empty_image(mlx_image_t *img);

// frame_update_utils.c
int	animation_frames_changed(cub3d_t *cub3d);
int	fps_frame_changed(cub3d_t *cub3d);
void	update_prev_frames(cub3d_t *cub3d);

// sort_distrations.c
distraction_t **create_array_of_distractions_ordered_by_dist(cub3d_t *cub3d);

// sort_enemies.c
t_enemy **create_array_of_enemies_ordered_by_dist(cub3d_t *cub3d);

// sort_keys.c
key_node_t	**create_array_of_keys_ordered_by_dist(cub3d_t *cub3d);

//---- INPUT -------------------------------------------------------------------

// handle_close.c
void	handle_close_window(void *param);

// handle_keys.c
void	get_input(mlx_key_data_t keydata, void *param);
void	handle_name_input(mlx_key_data_t keydata, cub3d_t *cub3d);
void	handle_pause_input(mlx_key_data_t keydata, cub3d_t *cub3d);
void	handle_start_input(mlx_key_data_t keydata, cub3d_t *cub3d);
void	handle_keyreleases(mlx_key_data_t keydata, cub3d_t *cub3d);
void	handle_level_input(mlx_key_data_t keydata, cub3d_t *cub3d);
void	handle_leaderboard_input(mlx_key_data_t keydata, cub3d_t *cub3d);
void	handle_game_input(mlx_key_data_t keydata, cub3d_t *cub3d);

// handle_mouse.c
void	hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param);
void	hook_mouse_scroll(double xdelta, double ydelta, void *param);
void	mouse_game(cub3d_t *cub3d);
void	mouse_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);
void	mouse_start_menu(cub3d_t *cub3d);
void	mouse_level_menu(cub3d_t *cub3d);
void	mouse_leaderboard(cub3d_t *cub3d, leaderboard_t *board);
void	mouse_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu);
void	mouse_entername_menu(cub3d_t *cub3d, name_menu_t *menu);
void	mouse_intro(cub3d_t *cub3d);

//---- MINIMAP -----------------------------------------------------------------

// minimap.c
void	move_minimap_x(cub3d_t *cub3d);
void	move_minimap_y(cub3d_t *cub3d);
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
void	raycast(cub3d_t *cub3d, player_t *player, ray_t *ray, double max_dist);
ray_t	*cast_ray(cub3d_t *cub3d, ray_t *ray);
void	set_wall_direction(ray_t *ray, player_t *player, int wall_flag);
int		wall_found(cub3d_t *cub3d, vector_t v_map_check);
int		goal_found(cub3d_t *cub3d, vector_t v_map_check);
int		obstacle_found(cub3d_t *cub3d, vector_t v_map_check, ray_t *ray, double dir);
vector_t	init_v_step(double dir);
dvector_t	init_step_size(double angle);
dvector_t	init_len(dvector_t start_pos, double dir, vector_t check, dvector_t step_size);
void	adjust(vector_t *v_map_check, ray_t *ray, vector_t v_step, dvector_t *v_ray_1d_length);
void	adjust_wall_flag(dvector_t *v_ray_1d_length, dvector_t step_size, int *wall_flag);
void	adjust_no_flag(dvector_t *v_ray_1d_length, dvector_t step_size);

//---- UTILS -------------------------------------------------------------------

// check_utils.c
int		get_current_level(cub3d_t *cub3d);
int		all_alpha(char *str);
int		all_digits(char *str);

// memory_utils.c
int		free_all(cub3d_t *cub3d, int i);
void	free_records(cub3d_t *cub3d);

void	free_info(char **info);
void	free_cub3d(cub3d_t *cub3d);
void	free_list(map_node_t *node);
void	free_record(record_t *record);
void	free_doors(door_pos_t *head);
void	free_keys(key_node_t *head);
void	free_level(cub3d_t *cub3d);
void	free_level_without_textures(cub3d_t *cub3d);
void	free_backup(level_t level);
void	free_keys_and_doors(cub3d_t *cub3d);
void	free_level_textures(cub3d_t *cub3d);
void	free_enemies(cub3d_t *cub3d);
void	free_minimap(cub3d_t *cub3d);
void	free_distractions(cub3d_t *cub3d);
void	disable_items(cub3d_t *cub3d);
void	free_delete_textures(level_t *level);
int		free_on_fail(cub3d_t *cub3d);

// error_utils.c
int		err(char *error_message);

// drawing_utils.c
void	draw_square(mlx_image_t *img, vector_t coord, int size, int color);
void	draw_circle(mlx_image_t *img, vector_t pos, int radius, int color);

void	draw_shroom_count(cub3d_t *cub3d);
void	disable_shroom(cub3d_t *cub3d);
void	enable_shroom(cub3d_t *cub3d);

//---- ENEMIES -------------------------------------------------------------------

int		init_enemy(cub3d_t *cub3d);
void	set_enemy_stats(cub3d_t *cub3d, int i);
ray_t	*init_ray_dir(double dir_to_enemy);
int		enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy, int i);
void	enemy_advance(cub3d_t *cub3d, int i);
void	enemy_vision(cub3d_t *cub3d);
void	draw_enemy(cub3d_t *cub3d, double dir_to_enemy, int index);
void	see_enemy(cub3d_t *cub3d, int i);
void	see_entities(cub3d_t *cub3d);
int		distraction(cub3d_t *cub3d, int i);
int		enemy_movement_ray(cub3d_t *cub3d, t_enemy *enemy, int i, double max_dist);

int		ray_to_enemy(cub3d_t *cub3d, double dir_to_enemy, double max_dist);
int		enemy_ray_to_distraction(cub3d_t *cub3d, dvector_t distraction, double dir_to, int i);
void	cause_distraction(cub3d_t *cub3d);
int		check_if_door_unlocked(cub3d_t *cub3d, int xcoord, int ycoord);
char	*create_file_path(int i, char *path);
int		check_if_player_is_seen(cub3d_t *cub3d, int i);

void	set_enemy_cursor_position(cub3d_t *cub3d, double cursor_angle,
	dvector_t *position);
void	enemy_cursor(cub3d_t *cub3d, double angle_from_player, double distance);

int		init_distractions(cub3d_t *cub3d);
void	count_distractions(cub3d_t *cub3d);
void	draw_distraction(cub3d_t *cub3d, double dir_to_distraction, int i);

void	eat(cub3d_t *cub3d, int i);
void	spin(cub3d_t *cub3d, int i, double at_target);
int		not_at_end(ray_t *ray, player_t player, t_enemy *enemy, int i);

int		wall_or_door_found(cub3d_t *cub3d, vector_t v_map_check);
void	see_keys(cub3d_t *cub3d, int i);
void	check_distraction(cub3d_t *cub3d, int i);

dvector_t	set_new_pos(cub3d_t *cub3d, int i);
int		check_each_other(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_first_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_second_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_third_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_fourth_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_fifth_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_sixth_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_seventh_eight(cub3d_t *cub3d, int i, dvector_t new_pos);
int		check_eighth_eight(cub3d_t *cub3d, dvector_t new_pos);
int		check_pos(cub3d_t *cub3d, int pos_y, int pos_x);

// texture general TODO
char	*create_file_path(int i, char *path);

//---- NULLIFY -----------------------------------------------------------------

void	nullify_everything(cub3d_t *cub3d);
void	nullify_cub3d(cub3d_t *cub3d);
void	nullify_minimap(minimap_t *minimap);
void	nullify_start_menu(start_menu_t *menu);
void	nullify_gameover_menu(gameover_menu_t *menu);
void	nullify_pause_menu(pause_menu_t *menu);
void	nullify_name_menu(name_menu_t *menu);
void	nullify_leaderboard(leaderboard_t *board);
void	nullify_level_menu(level_menu_t *menu);
void	nullify_enemy_frames(cub3d_t *cub3d);
void	nullify_gametimer(gametimer_t *timer);
void	nullify_hearts(heart_t *hearts);
void	nullify_png(png_t *png);
void	nullify_texture(texture_t *texture);

//---- EXTRA (REMOVE THESE BEFORE EVALUATION) ----------------------------------

// extra.c
void	print_level_info(level_t *level);
void	print_array(char **array, char *name);
void	print_map(char **map);
void	test(void);
void	print_settings(cub3d_t *cub3d);
void	print_letter_indexes(name_menu_t *menu, int backspace);

#endif
