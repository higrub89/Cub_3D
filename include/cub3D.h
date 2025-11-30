/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:25:24 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/25 16:11:07 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// =============================================================================
// 1. INCLUDES & DEFINES
// =============================================================================

# include "../libft/inc/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// --- PARSER SETTINGS ---
# define HDR_NO 0
# define HDR_SO 1
# define HDR_WE 2
# define HDR_EA 3
# define HDR_F 4
# define HDR_C 5
# define HDR_TOTAL 6
# define HDR_ALL_MASK 0x3F

// --- ENGINE SETTINGS ---
//# define WIN_WIDTH 1920
//# define WIN_HEIGHT 1080

// --- KEYCODES (Linux/X11) ---
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// =============================================================================
// 2. DATA STRUCTURES
// =============================================================================

// Gráficos y Texturas
typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

// Estado del Teclado
typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

// Matemáticas del Rayo
typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_ray;

// Motor Gráfico
typedef struct s_engine
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	t_img		screen_buff;
	t_img		textures[4];
}				t_engine;

// Jugador
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

// Assets del Parser
typedef struct s_assets
{
	char		*textures_path[4];
	char		*colors[2];
	int			colors_rgb[2];
	int			headers_mask;
}				t_assets;

// ESTRUCTURA PRINCIPAL
typedef struct s_grl
{
	// Modulo: Parser
	char		**map;
	char		**map_block;
	int			map_start;
	int			map_end;
	int			map_height;
	int			map_width;
	int			**solid_map;
	int			player_row;
	int			player_col;
	int			player_dir; // 0=N, 1=S, 2=E, 3=W
	t_assets	assets;

	// Modulo: Engine
	t_player	player;
	t_engine	engine;
	t_keys		keys;
	double		old_time;
}				t_grl;

// =============================================================================
// 3. FUNCTION PROTOTYPES (By File)
// =============================================================================

// -----------------------------------------------------------------------------
// MODULE 1: PARSE (code/1_parse/)
// -----------------------------------------------------------------------------

// parse.c
void			ft_ctrl_parse(t_grl *grl, const char *map_file);

// A1_map_array.c
void			ft_map_array(t_grl *grl, const char *map_file);
void			ft_validate_file_extension(t_grl *grl, const char *map_file);
int				ft_open_file(t_grl *grl, const char *map_file);
char			*ft_read_file_content(t_grl *grl, int fd);
int				ft_count_lines(char *buffer);

// A2_map_array_utils.c
char			**ft_allocate_lines_array(t_grl *grl, int line_count);
void			ft_split_buffer_lines(char *buffer, char **map);
void			ft_close_file(t_grl *grl, int fd);

// B1_headers.c
void			ft_headers(t_grl *grl);
int				ft_find_map_start_index(t_grl *grl, char **lines);
int				ft_find_map_end_index(t_grl *grl, char **lines, int map_start);
int				ft_is_line_empty(char *line);
int				ft_is_map_line(char *line);

// B2_find_map_end_index.c
void			ft_guard_against_map_gap(t_grl *grl, char **lines, int idx);
void			ft_process_header_line(t_grl *grl, char *line);
int				ft_extract_header(char *line, char **value);
void			ft_store_texture(t_grl *grl, int idx, char *value);
void			ft_store_color(t_grl *grl, int idx, char *value);

// C1_normalize_assets.c
void			ft_normalize_assets(t_grl *grl);

// D1_prepare_map_block.c
void			ft_prepare_map_block(t_grl *grl);

// -----------------------------------------------------------------------------
// MODULE 2: MAP VALIDATION (code/2_map/)
// -----------------------------------------------------------------------------

// map.c
void			ft_ctrl_map(t_grl *grl);

// A1_validate_map_closure.c
void			ft_validate_map_closure(t_grl *grl);

// A2_inter_spaces.c
void			ft_validate_internal_spaces(t_grl *grl);

// B1_validate_player_start.c
void			ft_validate_player_start(t_grl *grl);

// C1_validate_map_characters.c
void			ft_validate_map_characters(t_grl *grl);

// D1_validate_exterior_access.c
void			ft_validate_exterior_access(t_grl *grl);

// D2_Flood.c
void			ft_flood_fill_from_borders(t_grl *grl, int **visited);
void			ft_check_accessible_spaces(t_grl *grl, int **visited);

// E1_normalize_map_dimensions.c
void			ft_normalize_map_dimensions(t_grl *grl);

// F1_build_navigable_map.c
void			ft_build_navigable_map(t_grl *grl);

// G1_store_player_start.c
void			ft_store_player_start(t_grl *grl);

// H1_calculate_final_dimensions.c
void			ft_calculate_final_dimensions(t_grl *grl);

// -----------------------------------------------------------------------------
// MODULE 3: ENGINE (code/3_engine/)
// -----------------------------------------------------------------------------

// engine_init.c
void			ft_init_motor(t_grl *grl);
void			ft_load_textures(t_grl *grl);

// engine_hooks.c
void			ft_setup_hooks(t_grl *grl);
int				ft_game_loop(t_grl *grl);

// engine_render.c
void			ft_init_screen_buffer(t_grl *grl);
void			ft_put_pixel(t_grl *grl, int x, int y, int color);
void			ft_render_floor_ceiling(t_grl *grl);
void			ft_raycast_walls(t_grl *grl);

// engine_raycast.c
void			ft_init_ray(t_ray *ray, t_grl *grl, int x);
void			ft_calc_step(t_ray *ray, t_grl *grl);
void			ft_perform_dda(t_ray *ray, t_grl *grl);
void			ft_calc_wall_height(t_ray *ray, t_grl *grl);
void			ft_calc_texture_x(t_ray *ray, t_grl *grl);

// engine_movement.c
void			ft_move_player_pro(t_grl *grl, double move_speed);
void			ft_rotate_player_pro(t_grl *grl, double rot_speed);
double			get_delta_time(t_grl *grl);

// -----------------------------------------------------------------------------
// MODULE 4: INTEGRATION (code/4_integration/)
// -----------------------------------------------------------------------------

// bridge.c
void			ft_convert_data(t_grl *grl);

// -----------------------------------------------------------------------------
// MODULE 5: CLEANUP & UTILS (code/cleanUp/)
// -----------------------------------------------------------------------------

// cleanUp.c
void			ft_ctrl_cleanup(t_grl *grl, char *sterror, int exit_code);
void			ft_print_error(char *sterror);
void			ft_free(t_grl *grl);
void			ft_free_array(char **array);

#endif
