/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:29:44 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 12:45:41 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		count_enemies(t_cub3d *cub3d);
void		set_initial_direction(t_cub3d *cub3d);
int			count_t_minimapilesize(t_cub3d *cub3d, int size_percentage);
int			init_minimap(t_cub3d *cub3d);

//---- COLOR -------------------------------------------------------------------

uint32_t	get_pixel_color(t_texture texture, t_vector src);

// mix_color.c
int			get_color_mix(int color1, int color2);

// get_color.c
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

// set_color.c
int			set_rgba(int r, int g, int b, int a);
int			set_r(int rgba, int r);
int			set_g(int rgba, int g);
int			set_b(int rgba, int b);
int			set_a(int rgba, int a);

// transparency.c
int			set_transparency(int color, int transparency);

//---- CORE --------------------------------------------------------------------

int			read_all_levels(t_cub3d *cub3d);

// cursor.c
void		handle_cursor(t_cub3d *cub3d);

// game_over.c
void		level_finished(t_cub3d *cub3d);
void		game_over(t_cub3d *cub3d);

// hearts.c
int			load_heart_png(t_cub3d *cub3d);
int			init_full_hearts(t_cub3d *cub3d);
int			init_empty_hearts(t_cub3d *cub3d);
int			set_heart_positions(t_cub3d *cub3d);
int			put_hearts_to_window(t_cub3d *cub3d);
int			init_hearts(t_cub3d *cub3d);
void		delete_full_heart_texture(t_cub3d *cub3d, int i);
void		delete_empty_heart_texture(t_cub3d *cub3d, int i);
void		delete_full_heart_image(t_cub3d *cub3d, int i);
void		delete_empty_heart_image(t_cub3d *cub3d, int i);
void		delete_hearts(t_cub3d *cub3d);
void		disable_hearts(t_cub3d *cub3d);
void		enable_hearts(t_cub3d *cub3d);
void		adjust_hearts(t_cub3d *cub3d);

// records.c
void		create_time_string(char *time_str, int time);
int			add_record(t_cub3d *cub3d, t_record **records,
				int time, char *name);
int			read_records(t_cub3d *cub3d);
int			get_record_time(char *line, int *time);
int			get_record_name(char *line, char **name);
int			count_records(t_record *records);
t_record	*new_record(int time, char *name);
int			write_records(t_cub3d *cub3d, t_level *levels);
int			set_records(t_cub3d *cub3d, t_level *level, char **line, int fd);

// set_z_of_all_images.c
void		set_z_of_all_images(t_cub3d *cub3d);

// load_level.c
int			load_level(t_cub3d *cub3d, t_level *level);

// start_game.c
void		start_game(t_cub3d *cub3d);

// time.c
double		elapsed_time(t_cub3d *cub3d);
void		handle_fps(t_cub3d *cub3d);
void		set_fps(double *frame_time, int fps);
void		start_timer(t_cub3d *cub3d);
void		pause_timer(t_cub3d *cub3d);
void		continue_timer(t_cub3d *cub3d);
void		draw_timer(t_cub3d *cub3d);
void		update_timer(t_cub3d *cub3d);
void		free_three_strs(char *s1, char *s2, char *s3);

// halo
int			init_halo(t_cub3d *cub3d);
void		activate_halo(t_halo *halo, int color);
void		handle_halo(t_halo *halo);
void		draw_halo(mlx_image_t *img, t_halo *halo);
double		get_time_fade(t_halo *halo);

//---- PARSE -------------------------------------------------------------------

int			get_color(t_level *level, int element, char **info);
int			color_comma_checker(char *info);
int			all_elements_found(int *element_found);
void		remove_newline(char *line);
int			get_elements(t_level *level, int fd);
int			read_cub_file(t_level *level, char *map_path);
int			create_rectangular_map(t_level *level);
int			get_map(t_level *level, int fd);
int			add_map_line(t_map_node **first_node, char *line);
int			null_textures(t_level *level);
int			read_map(t_level *level, char *map_path);
int			copy_array(char **src, char **dst);
int			free_map_helper(t_level *level, int i);

// get_texture.c
int			get_texture(t_level *level, int element, char **info);
int			check_map_validity(char **map);
void		zero_map(char **map);

//---- DRAWING -----------------------------------------------------------------

void		draw_world(t_cub3d *cub3d);
void		draw_vertical_line(mlx_image_t *img, t_dvector start_d,
				t_dvector end_d, int color);
void		draw_line(mlx_image_t *img, t_dvector start_d,
				t_dvector end_d, int color);
void		draw_textured_line(t_cub3d *cub3d, t_dvector start,
				t_dvector end, t_ray ray);
void		draw_textured_line_close(t_cub3d *cub3d, t_dvector start,
				t_dvector end, t_ray ray);
void		draw_slider(mlx_image_t *img, t_slider *slider);

//---- INIT --------------------------------------------------------------------

// draw_menu_border.c
void		draw_menu_border(mlx_image_t *img);

// init_cub3d.c
int			count_minimap_tilesize(t_cub3d *cub3d, int size_percentage);
int			init_rays(t_cub3d *cub3d);
int			init_cub3d(t_cub3d *cub3d);
void		set_keys(t_keypress *keys);

// init menus
int			init_level_menu(t_cub3d *cub3d, t_level_menu *menu);
void		set_preview_values(t_minilevel *minilevel, t_level *level);
void		set_number_values(t_minilevel *minilevel);
void		draw_preview_map(t_minilevel *minilevel, t_level *level,
				char **backup);
int			load_png_level(t_level_menu *menu);
int			init_images_level(mlx_t *mlx, t_level_menu *menu);
void		draw_minimap_preview(t_minilevel *minilevel, t_level *level);
void		draw_border_image(t_minilevel *minilevel);

int			init_name_menu(t_cub3d *cub3d, t_name_menu *menu);
void		init_name_values(t_name_menu *menu);
void		draw_letter_box(mlx_image_t *img, t_letter_box *box);
void		init_letter_images(t_cub3d *cub3d, t_name_menu *menu);
void		set_letter_fields(t_name_menu *menu);

int			init_pause_menu(t_cub3d *cub3d, t_pause_menu *menu);
int			load_png_pause_menu(t_pause_menu *menu);
int			init_images_pause_menu(mlx_t *mlx, t_pause_menu *menu);
int			init_sensitivity_slider(t_cub3d *cub3d, t_pause_menu *menu);
void		init_checkboxes(t_pause_menu *menu);
void		init_checkbox_states(t_pause_menu *menu);
void		set_checkbox_values(t_pause_menu *menu);
void		init_settings(t_settings *settings);

int			init_start_menu(t_cub3d *cub3d, t_start_menu *menu);
int			load_png_start_menu(t_start_menu *menu);
int			init_images_start_menu(mlx_t *mlx, t_start_menu *menu);

int			init_leaderboard(t_cub3d *cub3d, t_leaderboard *board);
void		draw_times(mlx_t *mlx, t_record **records,
				t_leaderboard *board, int level);
void		draw_names(mlx_t *mlx, t_record **records,
				t_leaderboard *board, int level);
void		set_record_texts(t_cub3d *cub3d, t_leaderboard *board);
int			init_images_board(mlx_t *mlx, t_leaderboard *board);
int			load_png_board(t_leaderboard *board);

int			init_gameover_menu(t_cub3d *cub3d, t_gameover_menu *menu);
int			init_images_gameover(mlx_t *mlx, t_gameover_menu *menu);
int			load_png_gameover(t_gameover_menu *menu);
int			init_intro(t_cub3d *cub3d);

int			init_stars_textures(t_cub3d *cub3d);
int			init_door_textures(t_cub3d *cub3d);
int			init_doors_and_keys(t_cub3d *cub3d);
void		init_door_values(t_cub3d *cub3d);
int			init_door(t_cub3d *cub3d, int i, int j, int door_group_index);
int			load_door_textures(t_cub3d *cub3d);
int			init_enemy_frames(t_cub3d *cub3d);
int			set_indexes(t_cub3d *cub3d, int i);

int			count_keys(t_cub3d *cub3d, int i);
int			init_key(t_cub3d *cub3d, int i, int j, int key_group_index);
int			free_doors_and_keys(t_cub3d *cub3d);

int			init_shroom(t_cub3d *cub3d);

int			free_prev_start_menu(t_start_menu *menu, int i);
int			free_prev_level_menu(t_level_menu *menu, int i, int j);
int			free_prev_gameover_menu(t_gameover_menu *menu, int i);
int			free_prev_name_menu(t_name_menu *menu, int i);
void		free_textures_before_failed(t_texture *textures, int failed_index);
void		free_leaderboard(t_leaderboard *board);
void		free_shroom(t_cub3d *cub3d);
void		free_door_textures(t_cub3d *cub3d);
void		free_star_textures(t_cub3d *cub3d);
void		free_pause_menu(t_pause_menu *menu);
void		free_level_menu(t_level_menu *menu);
void		free_name_menu(t_name_menu *menu);
void		free_gameover_menu(t_gameover_menu *menu);
void		free_intro(t_cub3d *cub3d);
void		free_hearts(t_cub3d *cub3d);
void		free_start_menu(t_start_menu *menu);

//---- MENU --------------------------------------------------------------------

// delete_menu.c
void		delete_menus(t_cub3d *cub3d);
void		delete_start_menu(t_cub3d *cub3d, t_start_menu *menu);
void		delete_level_menu(t_cub3d *cub3d, t_level_menu *menu);
void		delete_leaderboard(t_cub3d *cub3d, t_leaderboard *board);
void		delete_name_menu(t_cub3d *cub3d, t_name_menu *menu);

// disable_menu.c

void		draw_background(mlx_image_t *img, int color);
void		draw_button(mlx_image_t *img, t_button *button);

// level menu
void		disable_level_menu(t_level_menu *menu);
void		enable_level_menu(t_level_menu *menu);
void		update_level_menu(t_cub3d *cub3d, t_level_menu *menu);

// leaderboard
void		draw_times(mlx_t *mlx, t_record **records,
				t_leaderboard *board, int level);
void		draw_names(mlx_t *mlx, t_record **records,
				t_leaderboard *board, int level);
void		disable_leaderboard(t_cub3d *cub3d, t_leaderboard *board);
void		enable_leaderboard(t_cub3d *cub3d, t_leaderboard *board);
void		update_leaderboard(t_cub3d *cub3d, t_leaderboard *board);

// name menu
void		disable_name_menu(mlx_t *mlx, t_name_menu *menu);
void		enable_name_menu(t_cub3d *cub3d, t_name_menu *menu);
void		update_name_menu(t_cub3d *cub3d, t_name_menu *menu);
int			update_letter(mlx_t *mlx, t_name_menu *menu, int *key, int i);
int			get_letter_first_third(t_cub3d *cub3d, t_name_menu *menu);
int			get_letter_second_third(t_cub3d *cub3d, t_name_menu *menu);
int			get_letter_last_third(t_cub3d *cub3d, t_name_menu *menu);
void		handle_backspace(t_cub3d *cub3d, t_name_menu *menu);
void		remove_record_image_pointers(t_cub3d *cub3d);
void		submit_name(t_cub3d *cub3d, t_name_menu *menu);
int			change_name(t_cub3d *cub3d, t_name_menu *menu);

// start menu
void		disable_start_menu(t_start_menu *menu);
void		enable_start_menu(t_start_menu *menu);
void		update_start_menu(t_cub3d *cub3d, t_start_menu *menu);

// gameover menu
void		disable_gameover_menu(mlx_t *mlx, t_gameover_menu *menu);
void		enable_gameover_menu(t_cub3d *cub3d,
				t_gameover_menu *menu, int win);
void		update_gameover_menu(t_cub3d *cub3d, t_gameover_menu *menu);

// intro menu
void		disable_intro(t_cub3d *cub3d);
void		enable_intro(t_cub3d *cub3d);

//---- PAUSE MENU --------------------------------------------------------------

int			get_marker_pos(t_cub3d *cub3d);
double		get_sensitivity(t_cub3d *cub3d);

// pause_text.c
void		add_category_text(t_cub3d *cub3d, t_pause_menu *menu);
void		add_checkbox_text(t_cub3d *cub3d, t_pause_menu *menu);

// pause_menu.c
void		update_settings(t_cub3d *cub3d, t_pause_menu *menu);
void		update_pause_settings(t_cub3d *cub3d, t_pause_menu *menu);
void		update_pause_menu(t_cub3d *cub3d, t_pause_menu *menu);
int			pause_menu_helper(t_cub3d *cub3d, t_pause_menu *menu);
void		draw_menu(t_cub3d *cub3d, t_pause_menu *menu);

void		disable_pause_menu(mlx_t *mlx, t_pause_menu *menu);
int			enable_pause_menu(t_cub3d *cub3d, t_pause_menu *menu);

// center.c
void		center(mlx_image_t *img);
void		center_vertically(mlx_image_t *img);
void		center_horizontally(mlx_image_t *img);

// hover.c
int			hover_image(t_cub3d *cub3d, mlx_image_t *img);
int			hover_button(t_cub3d *cub3d, t_button *button);
int			hover_rectangle(t_cub3d *cub3d, t_rectangle *rect);
int			hover_box(t_cub3d *cub3d, t_box *box);
int			hover_any_box(t_cub3d *cub3d, t_pause_menu *menu);

//---- DRAW --------------------------------------------------------------------

t_texture	find_texture(t_cub3d *cub3d, t_ray ray);
void		draw_filled_triangle(mlx_image_t *img,
				t_triangle *triangle, int color);
void		draw_rectangle(mlx_image_t *img, t_rectangle *rect);
void		draw_checkbox(t_cub3d *cub3d, t_box *box);
void		draw_hovered_checkbox(t_cub3d *cub3d, t_box *box);
int			get_door_key_color(t_cub3d *cub3d, int index);
void		draw_floor(t_cub3d *cub3d, t_frustum *frustum);
void		bresenham(mlx_image_t *img, t_vector start,
				t_vector end, int color);

//---- MATH --------------------------------------------------------------------

// math.c
int			min(int a, int b);
double		within_360(double degree);
double		within_two_pi(double radians);
double		to_radians(double degrees);
double		dist_between(t_vector a, t_dvector b);
double		dist_between_d_vectors(t_dvector a, t_dvector b);
double		lerp(t_range from, t_range to, double value);

// dda.c
int			find_end_point(t_cub3d *cub3d, t_player *player,
				double radians, t_dvector end);
int			obstacle_found_dist(t_cub3d *cub3d, t_vector v_map_check, int dist);
int			wall_checker(int wall_flag, t_dvector end, t_dvector pos);
int			all_keys_found(t_cub3d *cub3d, int i);

//---- PLAYER ------------------------------------------------------------------

// collision.c
void		collision_checker(t_cub3d *cub3d);
void		item_collected_checker(t_cub3d *cub3d);
void		player_is_hit(t_cub3d *cub3d, int i);
void		draw_health(t_cub3d *cub3d);
int			is_locked_door(t_cub3d *cub3d, int y, int x);

// player_movement.c
void		player_movement(t_cub3d *cub3d);
int			is_walking(t_cub3d *cub3d);
int			is_strafing(t_cub3d *cub3d);
void		player_rotation(t_cub3d *cub3d);

// fov.c
void		increase_fov(t_cub3d *cub3d);
void		decrease_fov(t_cub3d *cub3d);

//---- DOORS -------------------------------------------------------------------

int			get_door_index(char symbol);
int			get_key_index(char symbol);

//---- KEY COUNTS --------------------------------------------------------------

//key_count_string_utils.c
void		nullify_strings(char **text1, char **text2, char **text3);
void		free_non_null_strings(char *text1, char *text2, char *text3);

//key_counts.c
int			draw_key_counts(t_cub3d *cub3d);

//---- ANIMATION ---------------------------------------------------------------

// draw_game_entities.c
int			draw_game_entities(t_cub3d *cub3d);

// animation_utils.c
int			get_enemy_dir(t_enemy *enemy);
double		calculate_scale_factor(double dist, double normal_dist);

// assign_z_add_all.c
void		add_all_enemies(t_enemy **enemies, t_four_vector *indexes);
void		add_all_keys(t_key_node **keys, t_four_vector *indexes);
void		add_all_distractions(t_distract **distractions,
				t_four_vector *indexes);

// assign_z_depth_cases.c
void		case_all_3(t_enemy **enemies, t_key_node **keys,
				t_distract **distractions, t_four_vector *indexes);
void		case_without_keys(t_enemy **enemies, t_distract **distractions,
				t_four_vector *indexes);
void		case_without_distractions(t_enemy **enemies, t_key_node **keys,
				t_four_vector *indexes);
void		case_without_enemies(t_key_node **keys,
				t_distract **distractions, t_four_vector *indexes);

// assign_z_depth_utils.c
int			largest(double i, double j, double k);
void		init_indexes_and_z(t_cub3d *cub3d, t_four_vector *indexes);

// assign_z_depth.c
void		assign_z_depth_ordered_by_distance(t_cub3d *cub3d,
				t_enemy **enemies, t_key_node **keys,
				t_distract **distractions);

// draw_distractions.c
void		draw_all_distractions(t_cub3d *cub3d,
				t_distract **distractions);

// draw_enemies.c
void		draw_all_enemies(t_cub3d *cub3d, t_enemy **enemies);
void		see_enemy(t_cub3d *cub3d, int i);

// draw_keys.c
void		draw_all_keys(t_cub3d *cub3d);

// draw_utils.c
void		copy_pixel(mlx_image_t *img, t_uvector res, mlx_texture_t *texture,
				t_uvector src);
int			column_visible(t_cub3d *cub3d, double dist_to_player,
				int ray_index);
int			get_ray_i(double x, mlx_texture_t *texture, double factor,
				t_uvector res);
void		set_src_coordinates(t_uvector *src, t_uvector res,
				double factor, mlx_texture_t *texture);
void		empty_image(mlx_image_t *img);

// frame_update_utils.c
int			animation_frames_changed(t_cub3d *cub3d);
int			fps_frame_changed(t_cub3d *cub3d);
void		update_prev_frames(t_cub3d *cub3d);

// sort_distrations.c
t_distract	**create_array_of_distractions_ordered_by_dist(t_cub3d *cub3d);

// sort_enemies.c
t_enemy		**create_array_of_enemies_ordered_by_dist(t_cub3d *cub3d);

// sort_keys.c
t_key_node	**create_array_of_keys_ordered_by_dist(t_cub3d *cub3d);

//---- INPUT -------------------------------------------------------------------

// handle_close.c
void		handle_close_window(void *param);

// handle_keys.c
void		get_input(mlx_key_data_t keydata, void *param);
void		handle_name_input(mlx_key_data_t keydata, t_cub3d *cub3d);
void		handle_pause_input(mlx_key_data_t keydata, t_cub3d *cub3d);
void		handle_start_input(mlx_key_data_t keydata, t_cub3d *cub3d);
void		handle_keyreleases(mlx_key_data_t keydata, t_cub3d *cub3d);
void		handle_level_input(mlx_key_data_t keydata, t_cub3d *cub3d);
void		handle_leaderboard_input(mlx_key_data_t keydata, t_cub3d *cub3d);
void		handle_game_input(mlx_key_data_t keydata, t_cub3d *cub3d);

// handle_mouse.c
void		hook_mouse_buttons(enum mouse_key key, enum action action,
				enum modifier_key modifier, void *param);
void		hook_mouse_scroll(double xdelta, double ydelta, void *param);
void		mouse_game(t_cub3d *cub3d);
void		mouse_pause_menu(t_cub3d *cub3d, t_pause_menu *menu);
void		mouse_start_menu(t_cub3d *cub3d);
void		mouse_level_menu(t_cub3d *cub3d);
void		mouse_leaderboard(t_cub3d *cub3d, t_leaderboard *board);
void		mouse_gameover_menu(t_cub3d *cub3d, t_gameover_menu *menu);
void		mouse_entername_menu(t_cub3d *cub3d, t_name_menu *menu);
void		mouse_intro(t_cub3d *cub3d);

//---- MINIMAP -----------------------------------------------------------------

// minimap.c
void		move_minimap_x(t_cub3d *cub3d);
void		move_minimap_y(t_cub3d *cub3d);
void		update_minimap_player_pos(t_cub3d *cub3d);
void		minimap(t_cub3d *cub3d);

// minimap_draw_base.c
void		draw_minimap(t_cub3d *cub3d);
void		draw_minimap_border(t_cub3d *cub3d);

// minimap_draw_player.c
void		draw_minimap_player(t_cub3d *cub3d);
void		draw_minimap_playerdir(t_cub3d *cub3d);
void		draw_extras(t_cub3d *cub3d, int row, int column);
void		draw_fov(t_cub3d *cub3d);

// minimap_zoom.c
int			hover_minimap(t_cub3d *cub3d);
int			zoom_in_minimap(t_cub3d *cub3d);
int			zoom_out_minimap(t_cub3d *cub3d);

int			next_to_hidden(t_cub3d *cub3d, int row, int column);
int			get_hidden_color(t_cub3d *cub3d, int index, int row, int column);
void		draw_shroom(t_cub3d *cub3d, int row, int column, t_vector pos);

//---- RAYCASTING --------------------------------------------------------------

// raycasting.c
void		raycasting(t_cub3d *cub3d);
void		raycast(t_cub3d *cub3d, t_player *player,
				t_ray *ray, double max_dist);
t_ray		*cast_ray(t_cub3d *cub3d, t_ray *ray);
void		set_wall_direction(t_ray *ray, t_player *player, int wall_flag);
int			wall_found(t_cub3d *cub3d, t_vector v_map_check);
int			goal_found(t_cub3d *cub3d, t_vector v_map_check);
int			obstacle_found(t_cub3d *cub3d, t_vector v_map_check,
				t_ray *ray, double dir);
t_vector	init_v_step(double dir);
t_dvector	init_step_size(double angle);
t_dvector	init_len(t_dvector start_pos, double dir, t_vector check,
				t_dvector step_size);
void		adjust(t_vector *v_map_check, t_ray *ray, t_vector v_step,
				t_dvector *v_ray_1d_length);
void		adjust_wall_flag(t_dvector *v_ray_1d_length, t_dvector step_size,
				int *wall_flag);
void		adjust_no_flag(t_dvector *v_ray_1d_length, t_dvector step_size);

//---- UTILS -------------------------------------------------------------------

// check_utils.c
int			get_current_level(t_cub3d *cub3d);
int			all_alpha(char *str);
int			all_digits(char *str);

// memory_utils.c
void		free_enemy_frames(t_cub3d *cub3d);
int			free_all(t_cub3d *cub3d, int i);
void		free_records(t_cub3d *cub3d);

void		free_info(char **info);
void		free_cub3d(t_cub3d *cub3d);
void		free_list(t_map_node *node);
void		free_record(t_record *record);
void		free_doors(t_door_pos *head);
void		free_keys(t_key_node *head);
void		free_level(t_cub3d *cub3d);
void		free_level_without_textures(t_cub3d *cub3d);
void		free_backup(t_level level);
void		free_keys_and_doors(t_cub3d *cub3d);
void		free_level_textures(t_cub3d *cub3d);
void		free_enemies(t_cub3d *cub3d);
void		free_minimap(t_cub3d *cub3d);
void		free_distractions(t_cub3d *cub3d);
void		disable_items(t_cub3d *cub3d);
void		free_delete_textures(t_level *level);
int			free_on_fail(t_cub3d *cub3d);

// error_utils.c
int			err(char *error_message);

// drawing_utils.c
void		draw_square(mlx_image_t *img, t_vector coord, int size, int color);
void		draw_circle(mlx_image_t *img, t_vector pos, int radius, int color);

void		draw_shroom_count(t_cub3d *cub3d);
void		disable_shroom(t_cub3d *cub3d);
void		enable_shroom(t_cub3d *cub3d);

//---- ENEMIES ----------------------------------------------------------------

int			init_enemy(t_cub3d *cub3d);
void		set_enemy_stats(t_cub3d *cub3d, int i);
void		init_file_paths(char **idle_file_paths, char **walking_file_paths,
				char **hunting_file_paths);
t_ray		*init_ray_dir(double dir_to_enemy);
int			enemy_ray(t_cub3d *cub3d, t_player player, t_enemy *enemy, int i);
void		enemy_advance(t_cub3d *cub3d, int i);
void		enemy_vision(t_cub3d *cub3d);
void		draw_enemies(t_cub3d *cub3d);
int			distraction(t_cub3d *cub3d, int i);
int			enemy_movement_ray(t_cub3d *cub3d, t_enemy *enemy,
				int i, double max_dist);

int			ray_to_enemy(t_cub3d *cub3d, double dir_to_enemy, double max_dist);
int			enemy_ray_to_distraction(t_cub3d *cub3d, t_dvector distraction,
				double dir_to, int i);
void		cause_distraction(t_cub3d *cub3d);
int			check_if_door_unlocked(t_cub3d *cub3d, int xcoord, int ycoord);
char		*create_file_path(int i, char *path);
int			check_if_player_is_seen(t_cub3d *cub3d, int i);

void		set_enemy_cursor_position(t_cub3d *cub3d, double cursor_angle,
				t_dvector *position);
void		enemy_cursor(t_cub3d *cub3d, double angle_from_player,
				double distance);

int			init_distractions(t_cub3d *cub3d);
void		count_distractions(t_cub3d *cub3d);
void		draw_distraction(t_cub3d *cub3d, double dir_to_distraction, int i);

void		eat(t_cub3d *cub3d, int i);
void		spin(t_cub3d *cub3d, int i, double at_target);
int			not_at_end(t_ray *ray, t_player player, t_enemy *enemy, int i);

int			wall_or_door_found(t_cub3d *cub3d, t_vector v_map_check);
void		see_key(t_cub3d *cub3d, double dir_to_key, t_key_node *key);
void		see_distraction(t_cub3d *cub3d, double dir_to_distraction, int i);

t_dvector	set_new_pos(t_cub3d *cub3d, int i);
int			check_each_other(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_first_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_second_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_third_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_fourth_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_fifth_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_sixth_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_seventh_eight(t_cub3d *cub3d, int i, t_dvector new_pos);
int			check_eighth_eight(t_cub3d *cub3d, t_dvector new_pos);
int			check_pos(t_cub3d *cub3d, int pos_y, int pos_x);

// texture general TODO
char		*create_file_path(int i, char *path);
int			find_index(t_cub3d *cub3d);

//---- NULLIFY -----------------------------------------------------------------

void		nullify_everything(t_cub3d *cub3d);
void		nullify_cub3d(t_cub3d *cub3d);
void		nullify_minimap(t_minimap *minimap);
void		nullify_start_menu(t_start_menu *menu);
void		nullify_gameover_menu(t_gameover_menu *menu);
void		nullify_pause_menu(t_pause_menu *menu);
void		nullify_name_menu(t_name_menu *menu);
void		nullify_leaderboard(t_leaderboard *board);
void		nullify_level_menu(t_level_menu *menu);
void		nullify_enemy_frames(t_cub3d *cub3d);
void		nullify_gametimer(t_gametimer *timer);
void		nullify_hearts(t_heart *hearts);
void		nullify_png(t_png *png);
void		nullify_texture(t_texture *texture);

#endif
