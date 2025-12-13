#include "../include/cub3d.h"
#define BONUS_TILE 4

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

            x++;
        }
        y++;
    }
    draw_rect(game, (int)(game->player.pos_x * 8 / TILE_SIZE), 
              (int)(game->player.pos_y * 8 / TILE_SIZE), 4, 0xFF0000);
} 

//ms7 had file fih ra minimap li mrndiroch