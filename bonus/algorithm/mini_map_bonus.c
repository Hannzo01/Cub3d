/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:04:02 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/09 12:27:31 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void draw_rect(t_game *game, int x_pixel, int y_pixel, int size, int color)
{ // size == toll d rec 
    int x;
    int y;

    x = 0;
    while (x < size)
    {
        y = 0;
        while (y < size)
        {
            if ((x_pixel + x) < SCREEN_W && (y_pixel + y) < SCREEN_H)
                put_pixel(&game->screen, x_pixel + x, y_pixel + y, color);
            y++;
        }
        x++;
    }
}

void draw_line(t_game *game)
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int i;

    start_x = (int)(game->player.pos_x * BONUS_TILE / TILE_SIZE + 1.75);
    start_y = (int)(game->player.pos_y * BONUS_TILE / TILE_SIZE );
    i = 0;
    while (i < 10)
    {
        end_x = start_x + (int)(game->player.dir_x * i);
        end_y = start_y + (int)(game->player.dir_y * i);
        put_pixel(&game->screen, end_x, end_y , 0xFFFFFF);
        i++;
    }
}

void render_minimap(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width && game->map.layout[y][x])
        {
            if (game->map.layout[y][x] == '1')
                draw_rect(game, x * 8, y * 8, 8, 0xFFFFFF);
            // else
            //     draw_rect(game, x * 8, y * 8, 8, 0x159801); // 7ydi hadi lmbghiti ta loun f l2ard

            x++;
        }
        y++;
    }
    draw_rect(game, (int)(game->player.pos_x * 8 / TILE_SIZE), 
              (int)(game->player.pos_y * 8 / TILE_SIZE), 4, 0xFF0000);
    draw_line(game);
} 
