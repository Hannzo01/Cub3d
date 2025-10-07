/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/10/04 16:11:52 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void put_pixel_on_buffer(t_texture *buffer, int color, int x, int y)
{
    char *pixel = buffer->image_data +  (x * buffer->size_line + y * (buffer->bits_per_pixel / 8)); // 
    *(int *)pixel = color;
}

int get_textures_pixel(t_texture *texture, int x, int y)
{   
    char *pixel;

    pixel = texture->image_data +  (x * texture->size_line + y * (texture->bits_per_pixel / 8)); // 
    // size line equal 128 mean 32 bytes (most of time)
    // bit_per_pixel equal 32  mean for bytes for pixel in my project
    return (*(int *)pixel);
}

static void copy_textures_to_buffer(t_game *game, t_texture *texture, int dest_x, int dest_y)
{
    int x =0;
    int y = 0;
    int color;

    while (x < 32)
    {
        y = 0;
        while (y < 32)
        {
            color = get_textures_pixel(texture, x, y);
            put_pixel_on_buffer(&game->new_image, color, x + dest_x, y + dest_y);
            y++;
        }
        x++;
    }
}

void get_player_position(t_game *game, int *new_x, int *new_y)
{
    if (game->player.up)
        *new_x = -1;
    if (game->player.down)
        *new_x = 1;
    if (game->player.right)
        *new_y = 1;
    if (game->player.left)
        *new_y = -1;

    game->player.up = 0;
    game->player.down = 0;
    game->player.right = 0;
    game->player.left = 0;
}

int rander_map(t_game *game)
{

    int i = 0;
    int j = 0;
    float x ,y;
    int new_x = 0, new_y = 0;
    int a = 0, b = 0;

    x = game->player.x;
    y = game->player.y;
    if (game->player.up)
        
    get_player_position(game, &new_x, &new_y);
    if (new_x)
    {
        x = game->player.x + (new_x * 4);
        a = x;
        if (x > (float)a)
            a = (x / 32 + 1) * 32;
        if (game->map[a / 32 + 1][(int)(y / 32)] == '1')
            return 0;
    }
    if (new_y)
    {
        y = y + (new_y * 4);
        b = y;
        if (y > (float)b)
            b = (y / 32  + 1) * 32;
        if (game->map[(int)(x / 32)][b / 32] == '1')
            return 0;
    }

    if (game->map[(int)(x / 32)][(int)(y /32)] == '1')
        return 0;
    game->player.x = x;
    game->player.y = y;   
        
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
               copy_textures_to_buffer(game, &game->minimap.wall, i * 32, j * 32);
            if (game->map[i][j] == '0')
                copy_textures_to_buffer(game, &game->minimap.floor, i * 32, j * 32);              
            j++;
        }
        i++;
    }
    copy_textures_to_buffer(game, &game->minimap.player, x , y);   
    mlx_put_image_to_window(game->mlx, game->window, game->new_image.image, 0, 0);
    return (0);
}

