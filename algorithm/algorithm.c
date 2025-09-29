/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/28 13:19:41 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void data_init(t_game *game, t_map *data)
{
    /*------------------------open new image-----------------------*/
    game->new_image.image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->new_image.image_data = mlx_get_data_addr(game->new_image.image ,\
        &game->new_image.bits_per_pixel, &game->new_image.size_line ,\
        &game->new_image.endian);
    ft_memset(game->new_image.image_data, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    /*------------------------load textuers -----------------------*/

    game->east.image = mlx_xpm_file_to_image(game->mlx, \
        data->map_info->ea, &(int){tile_size}, &(int){tile_size});
    game->north.image = mlx_xpm_file_to_image(game->mlx,\
         data->map_info->no, &(int){tile_size}, &(int){tile_size});
    game->south.image = mlx_xpm_file_to_image(game->mlx,\
         data->map_info->so, &(int){tile_size}, &(int){tile_size});
    game->west.image = mlx_xpm_file_to_image(game->mlx, \
        data->map_info->we, &(int){tile_size}, &(int){tile_size});
/*---------------------------get textures data--------------------------*/
    game->east.image_data = mlx_get_data_addr(game->east.image, 
        &game->east.bits_per_pixel, &game->east.size_line, &game->east.endian);

    game->north.image_data = mlx_get_data_addr(game->north.image, 
        &game->north.bits_per_pixel, &game->north.size_line, &game->north.endian);

    game->south.image_data = mlx_get_data_addr(game->south.image, 
        &game->south.bits_per_pixel, &game->south.size_line, &game->south.endian);

    game->west.image_data = mlx_get_data_addr(game->west.image, 
        &game->west.bits_per_pixel, &game->west.size_line, &game->west.endian);

/*---------------------------testing part--------------------------*/   
    game->minimap.player.image = mlx_xpm_file_to_image(game->mlx, \
        "textures/player.xpm", &(int){tile_size}, &(int){tile_size});
    game->minimap.wall.image = mlx_xpm_file_to_image(game->mlx, \
        "textures/wall.xpm", &(int){tile_size}, &(int){tile_size});
    game->minimap.floor.image = mlx_xpm_file_to_image(game->mlx, \
        "textures/floor.xpm", &(int){tile_size}, &(int){tile_size});
                    /*get textures data*/
    game->minimap.player.image_data = mlx_get_data_addr(game->minimap.player.image ,\
        &game->minimap.player.bits_per_pixel, &game->minimap.player.size_line, \
        &game->minimap.player.endian);

    game->minimap.wall.image_data = mlx_get_data_addr(game->minimap.wall.image ,\
        &game->minimap.wall.bits_per_pixel, &game->minimap.wall.size_line, \
        &game->minimap.wall.endian);
    
    game->minimap.floor.image_data = mlx_get_data_addr(game->minimap.floor.image ,\
        &game->minimap.floor.bits_per_pixel, &game->minimap.floor.size_line, \
        &game->minimap.floor.endian);
        
}

t_game *fill_data(t_map *data)
{
    t_game *game;

    game = gc_malloc(sizeof(t_game), data);
    ft_memset(game, 0, sizeof(t_game));
    game->map = data->map;
    game->f = data->map_info->f;
    game->c = data->map_info->c;
    game->length = data->max_len;
    game->height = data->height;
    game->player.y = data->p_x * 32;
    game->player.x = data->p_y * 32;
    game->player.direction = game->map[game->player.x][game->player.y];
    game->map[game->player.x][game->player.y] = '0';
    return (game);
}
int handel_exit(void *game)
{
    (void)game;
    exit(1);
}


void algorithm(t_map *data)
{
    t_game *game;

    game = fill_data(data);
    game->mlx = mlx_init();
    if (!game->mlx)
        exit (1);
    game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT , "cub3d");
    if (!game->window)
        exit (1);
    data_init(game, data);
     rander_map(game);
    mlx_hook(game->window, 17, 0, handel_exit, NULL);
    mlx_hook(game->window, 2, 1L<<0, player_movment, game);;
    // mlx_loop_hook(game->mlx, rander_map, game);
    mlx_loop(game->mlx);
}