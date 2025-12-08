/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/08 19:28:38 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/cub3d2.h"

t_game *fill_data(t_map *data)
{
    t_game *game;

    game = gc_malloc(sizeof(t_game), data);
    ft_memset(game, 0, sizeof(t_game));
    
    game->map.layout = data->map;
    game->map.width = data->max_len;
    game->map.height = data->height;

    // Textures
    game->map.no_texture = data->map_info->no;
    game->map.so_texture = data->map_info->so;
    game->map.we_texture = data->map_info->we;
    game->map.ea_texture = data->map_info->ea;

    // Colors
    game->map.floor_color = data->map_info->f;
    game->map.ceil_color = data->map_info->c;

    // Player position (center of tile)
    game->player.pos_x = (double)data->p_x * tile_size + tile_size / 2.0;
    game->player.pos_y = (double)data->p_y * tile_size + tile_size / 2.0;

    // Set direction based on map character
    char spawn_dir = data->map[data->p_y][data->p_x];
    
    if (spawn_dir == 'N') {
        game->player.dir_x = 0.0; game->player.dir_y = -1.0;
        game->player.plane_x = 0.66; game->player.plane_y = 0.0;
    } else if (spawn_dir == 'S') {
        game->player.dir_x = 0.0; game->player.dir_y = 1.0;
        game->player.plane_x = -0.66; game->player.plane_y = 0.0;
    } else if (spawn_dir == 'W') {
        game->player.dir_x = -1.0; game->player.dir_y = 0.0;
        game->player.plane_x = 0.0; game->player.plane_y = -0.66;
    } else { // E or default
        game->player.dir_x = 1.0; game->player.dir_y = 0.0;
        game->player.plane_x = 0.0; game->player.plane_y = 0.66;
    }

    return (game);
}

int handle_exit(void *data)
{
    (void)data;
    exit(0);
    return (0);
}

void algorithm(t_map *data)
{
    t_game *game;

    game = fill_data(data);
    game->mlx = mlx_init();
    if (!game->mlx)
        return ;    
    game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H , "cub3d");
    if (!game->win)
        return ;
    game->screen.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
    game->screen.addr = mlx_get_data_addr(game->screen.img,
                                         &game->screen.bpp,
                                         &game->screen.line_len,
                                         &game->screen.endian);
    
    mlx_hook(game->win, 17, 0, handle_exit, game);
    mlx_hook(game->win, 2, 1L<<0, player_movment, game);
    mlx_loop_hook(game->mlx, render_map, game);
    mlx_loop(game->mlx);
}