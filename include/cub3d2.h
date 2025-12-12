/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:31:42 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/12 23:52:17 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D2_H
# define CUB3D2_H

// # include "/home/sechlahb/Desktop/minilibx-linux/mlx.h"
# include "/home/kemzouri/minilibx-linux/mlx.h"
# define SCREEN_W 1080
# define SCREEN_H 720

# define TILE_SIZE 32
# define MOVE_SPEED 4.0
# define PLAYER_SIZE 8

/*5 degrees in radians*/
// # define ROT_SPEED (5.0 * 3.14159265358979323846 / 180.0)
# define ROT_SPEED 0.08726646
// drtlha hnayaaa resultat hit li lfo9 mabghthach norminette
# define COLOR_BG 0x1E1E1E
# define COLOR_WALL 0x888888
# define COLOR_EMPTY 0x2E2E2E
# define COLOR_RAY 0xFFFF00
# define COLOR_PLAYER 0x00FF00

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307
# define UP_KEY 65362
# define LEFT_KEY 65361
# define DOWN_KEY 65364
# define RIGHT_KEY 65363

typedef struct s_map	t_map;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				angle;
}						t_player;

typedef struct s_img
{
	char				*xpm;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_maps
{
	char				**layout;
	int					width;
	int					height;
	t_img				no_texture;
	t_img				so_texture;
	t_img				we_texture;
	t_img				ea_texture;
	int					*floor_color;
	int					*ceil_color;
}						t_maps;

typedef struct s_game
{
	t_map				*data;
	void				*mlx;
	void				*win;
	t_img				screen;
	t_maps				map;
	t_player			player;
}						t_game;

typedef struct s_ray
{
	double				dir_x;
	double				dir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					side;
}						t_ray;

typedef struct s_tex_ctx
{
	t_img	*tex;
	int		tx;
	double	step;
	double	pos;
	int		draw_start;
	int		draw_end;
	int		x;
}	t_tex_ctx;

#endif