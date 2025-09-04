/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:02:21 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/04 23:41:14 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -L/usr/include/minilibx-linux -lmlx -lX11 -lXext 

// #include "mlx.h"
#include "/home/sechlahb/Desktop/minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    char **map;
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int F[3];
    int C[3];
    // F 220,100,0 exemple for floor color  -- F mean floor
    // C 225,30,0 exemple for Ceiling color -- C mean ceiling
} t_data;

typedef struct s_cub3d
{
    void *mlx;
    void *window;
    void *img_nprth;
    void *img_south;
    void *img_west;
    void *img_east;
    t_data data;
} t_cub3d;

int handler(t_cub3d *cub3d)
{
    (void) cub3d;
    printf("gamme closed\n");
    exit (0);
}

int main()
{
    t_cub3d cub3d;
    
    char map[10][11];
    map[0] = "1111111111";
    map[1] = "1000000001";
    map[2] = "1001110001";
    map[3] = "1000000001";
    map[4] = "1001111001";
    map[5] = "1000000001";
    map[6] = "1000N00001";
    map[7] = "1000000001";
    map[8] = "1111111111";
    map[9] = NULL;
    cub3d.data.north_texture = "textures/north.xpm";
    cub3d.data.east_texture = "textures/east.xpm";
    cub3d.data.south_texture = "textures/south.xpm";
    cub3d.data.west_texture = "textures/west.xpm";
    cub3d.mlx = mlx_init();
    cub3d.window = mlx_new_window(cub3d.mlx, 800, 600, "cub3d");
    mlx_hook(cub3d.window, 17, 0, handler, &cub3d);
    mlx_loop(cub3d.mlx);
}