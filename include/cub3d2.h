/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:31:42 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/08 19:26:14 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D2_H
# define CUB3D2_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"

// Forward declaration for t_map from cub3d.h
typedef struct s_map t_map;

# define SCREEN_W 1080
# define SCREEN_H 720
# define tile_size 64

// Key codes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}   t_player;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_maps
{
    char    **layout;
    int     width;
    int     height;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     *floor_color;
    int     *ceil_color;
}   t_maps;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       screen;
    t_maps      map;
    t_player    player;
}   t_game;

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     side;
}   t_ray;

// Algorithm functions
void    algorithm(t_map *data);
t_game  *fill_data(t_map *data);

// Raycasting
void    cast_ray(t_game *game, int x);
void    perform_dda(t_game *game, t_ray *ray);

// Rendering
int     render_map(t_game *game);
void    draw_wall(t_game *game, t_ray *ray, int x);
void    put_pixel(t_img *img, int x, int y, int color);

// Player
int     player_movment(int keycode, void *param);
void    move_player(t_game *game, double move_x, double move_y);
void    rotate_player(t_game *game, double angle);

// Helpers (if needed for linking)
void    *gc_malloc(int size, t_map *game);
void	*ft_memset(void *s, int c, size_t n);

#endif