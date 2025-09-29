/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:31:42 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/28 14:11:47 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D2_H
# define CUB3D2_H

# include "/home/sechlahb/Desktop/minilibx-linux/mlx.h"
#include "cub3d.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

# define w_key 119
# define a_key 97
# define s_key 115
# define d_key 100
# define  esc 65307

# define up_key 65362
# define left_key 65361
# define down_key 65364
# define right_key 6536

# define tile_size 32

typedef struct s_player
{
    int down;
    int up;
    int left;
    int right;
    void *player_img;
    int x;
    int y;
    char direction;
    float dir_x;
    float dir_y;
    float plane_x;
    float plane_y;
}t_player;

typedef struct s_texture
{
    void *image;
    char *image_data;
    int bits_per_pixel;
    int size_line;
    int endian; 
} t_texture;

typedef struct s_minimap
{
    t_texture wall;
    t_texture player;
    t_texture floor;
} t_minimap;

typedef struct s_game
{
    char **map;
    int height;
    int length;
    void *mlx;
    void *window;
    t_texture new_image;
    t_minimap minimap;
    t_texture north;
    t_texture south;
    t_texture west;
    t_texture east;
    int *f;
    int *c;
    t_player player;
    
}   t_game;

/*--------------raycasting----------------*/
// void algorithm(t_map *game);


#endif