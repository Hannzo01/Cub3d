/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:02:21 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/09 11:16:24 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -L/usr/include/minilibx-linux -lmlx -lX11 -lXext 

// #include "mlx.h"
#include "/home/sechlahb/Desktop/minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    void *img_north;
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

void init(t_cub3d *cub3d)
{

    cub3d->img_north = mlx_xpm_file_to_image(cub3d->mlx, "textures/north.xpm",
			&(int){64}, &(int){64});
    cub3d->img_south = mlx_xpm_file_to_image(cub3d->mlx, "textures/south.xpm",
			&(int){64}, &(int){64});
    cub3d->img_west = mlx_xpm_file_to_image(cub3d->mlx, "textures/west.xpm",
			&(int){64}, &(int){64});
    cub3d->img_east = mlx_xpm_file_to_image(cub3d->mlx, "textures/east.xpm",
			&(int){64}, &(int){64});
}


void draw_line(t_cub3d *cub3d, int x0, int y0, int x1, int y1, int color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        mlx_pixel_put(cub3d->mlx, cub3d->window, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}




void rander_map(t_cub3d *cub3d) 
{
    int i;
    int j;

    i = 0;
    while (cub3d->data.map[i])
    {
        j = 0;
        while (cub3d->data.map[i][j])
        {
            if (i == 1 && j == 1)
            {
                int s = 0;
                int k = 0;
                while ( k < 64)
                {
                    s = 0;
                    while (s < 64)
                    {
                        mlx_pixel_put(cub3d->mlx, cub3d->window, j * 64 + k , i * 64 + s, 0xffffff);
                        s++;
                    }
                    k++;
                    
                }
            }
            if (cub3d->data.map[i][j] == '1')
            {
                mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
                     cub3d->img_north, j * 64, i * 64);
                j++;
            }
            else if(cub3d->data.map[i][j] == 'P')
            {
                mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
                     cub3d->img_west, j * 64, i * 64);
                // mlx_pixel_put(cub3d->mlx, cub3d->window, (j + 1) * 64 , i * 64 , 0xff0000);
                j++;
                int a;
                int b;
                int c;
                int f = 24;
                b = 16;
                c = 48;
                while (cub3d->data.map[i][j] != '1')
                {
                    a = 0;
                    while (a < 64)
                    {
                        mlx_pixel_put(cub3d->mlx, cub3d->window, (j * 64) + a , (i * 64) + 32 , 0xff0000); // high
                        
                        mlx_pixel_put(cub3d->mlx, cub3d->window, (j * 64) +  a, (i * 64) + f, 0xff0000); //
                        
                        mlx_pixel_put(cub3d->mlx, cub3d->window, (j * 64) + a  , (i * 64) + b  , 0xff0000); // middle
                        
                        mlx_pixel_put(cub3d->mlx, cub3d->window, (j * 64) + a , (i * 64) + c  , 0xff0000); // below
                        a += 2;
                        f -= 1;
                        b -= 1;
                        c += 1;
                    }
                    j++;
                }
                // draw_line(cub3d, j * 64 + 32, i * 64 + 32, j * 64, i * 64, 0xFF0000);
            }else
                j++;
        }
        i++;
    }
}

void fill_mapp(t_cub3d *cub3d)
{
    char **map;

    map = malloc(sizeof(char *) * 10);
    map[0] = strdup("1111111111");
    map[1] = strdup("1000000001");
    map[2] = strdup("1001110001");
    map[3] = strdup("1000000001");
    map[4] = strdup("1001111001");
    map[5] = strdup("1000101001");
    map[6] = strdup("1000P00001");
    map[7] = strdup("1000000001");
    map[8] = strdup("1111111111");
    map[9] = NULL;
    cub3d->data.map = map;
    cub3d->data.north_texture = strdup("textures/north.xpm");
    cub3d->data.east_texture = strdup("textures/east.xpm");
    cub3d->data.south_texture = strdup("textures/south.xpm");
    cub3d->data.west_texture = strdup("textures/west.xpm");
}

int main()
{
    t_cub3d cub3d;
    
    cub3d.mlx = mlx_init();
    cub3d.window = mlx_new_window(cub3d.mlx, 10 * 64, 9 * 64, "cub3d");

    fill_mapp(&cub3d);
    init(&cub3d);
    rander_map(&cub3d);

    mlx_hook(cub3d.window, 17, 0, handler, &cub3d);
    mlx_loop(cub3d.mlx);
}void