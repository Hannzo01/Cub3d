/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:21:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/08 21:08:30 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
// int create_trgb(int t, int r, int g, int b)
// {
//     int rgb;

//     rgb = 0;
//     rgb += t << 24;
//     rgb += r << 16;
//     rgb += g << 8;
//     rgb += b;
//     return rgb;
// }

void draw_wall(t_game *game, t_ray *ray, int x)
{
    // Prevent division by zero or extremely large heights
    if (ray->perp_wall_dist < 0.0001)
        ray->perp_wall_dist = 0.0001;

    // Calculate height of line to draw on screen
    int line_height = (int)(SCREEN_H / ray->perp_wall_dist);
    
    // Calculate lowest and highest pixel to fill in current stripe
    int draw_start = -line_height / 2 + SCREEN_H / 2;
    if (draw_start < 0) draw_start = 0;
    
    int draw_end = line_height / 2 + SCREEN_H / 2;
    if (draw_end >= SCREEN_H) draw_end = SCREEN_H - 1;
    
    // Choose wall color based on direction (simple shading)
    // Changed colors to be more distinct:
    // East: Red, West: Green, South: Blue, North: Yellow
    int color;
    if (ray->side == 0) // Vertical wall
        color = (ray->step_x > 0) ? 0xEA2027 : 0x009432; 
    else // Horizontal wall
        color = (ray->step_y > 0) ? 0x0652DD : 0xFFC312; 
    
    // Darken color for y-side walls to give depth
    if (ray->side == 1)
        color = (color >> 1) & 8355711;

    // Draw Ceiling
    int ceil_c = create_trgb(0, game->map.ceil_color[0], game->map.ceil_color[1], game->map.ceil_color[2]);
    for (int y = 0; y < draw_start; y++)
        put_pixel(&game->screen, x, y, ceil_c);
    
    // Draw Wall
    for (int y = draw_start; y < draw_end; y++)
        put_pixel(&game->screen, x, y, color);
    
    // Draw Floor
    int floor_c = create_trgb(0, game->map.floor_color[0], game->map.floor_color[1], game->map.floor_color[2]);
    for (int y = draw_end; y < SCREEN_H; y++)
        put_pixel(&game->screen, x, y, floor_c);
}

int render_map(t_game *game)
{
    int x;

    x = 0;
    while (x < SCREEN_W)
    {
        cast_ray(game, x);
        x++;
    }   
    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    return (0);
}
