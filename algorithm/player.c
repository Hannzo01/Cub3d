/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:21:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/09 17:20:16 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void rotate_player(t_game *game, double angle)
{
    // Rotate direction vector
    double old_dir_x = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
    
    // Rotate camera plane
    double old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

int check_collision(t_game *game, double new_x, double new_y)
{
    int top_left_x;
    int top_left_y;
    int top_right_x;
    int top_right_y;
    int bottom_left_x;
    int bottom_left_y;
    int bottom_right_x;
    int bottom_right_y;

    top_left_x = (int)(new_x / TILE_SIZE);
    top_left_y = (int)(new_y / TILE_SIZE);
    top_right_x = (int)((new_x + PLAYER_SIZE) / TILE_SIZE);
    top_right_y = (int)(new_y / TILE_SIZE);
    bottom_left_x = (int)(new_x / TILE_SIZE);
    bottom_left_y = (int)((new_y + PLAYER_SIZE) / TILE_SIZE);
    bottom_right_x = (int)((new_x + PLAYER_SIZE) / TILE_SIZE);
    bottom_right_y = (int)((new_y + PLAYER_SIZE) / TILE_SIZE);
    if (top_left_x < 0 || top_left_y < 0 || bottom_right_x >= game->map.width || bottom_right_y >= game->map.height)
        return (1);
    if (game->map.layout[top_left_y][top_left_x] == '1')
        return (1);
    if (game->map.layout[top_right_y][top_right_x] == '1')
        return (1);
    if (game->map.layout[bottom_left_y][bottom_left_x] == '1') 
        return (1);
    if (game->map.layout[bottom_right_y][bottom_right_x] == '1') 
        return (1);
    return (0);
}

void move_player(t_game *game, double move_x, double move_y)
{
    double new_x = game->player.pos_x + move_x;
    double new_y = game->player.pos_y + move_y;
    
    // Check collision for X and Y separately to allow sliding along walls
    if (!check_collision(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (!check_collision(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

int player_movment(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    double move_speed = 5.0;
    double rot_speed = 0.05;
    
    if (keycode == KEY_ESC)
        exit(0);
        
    // Move forward/backward
    if (keycode == KEY_W)
        move_player(game, game->player.dir_x * move_speed, game->player.dir_y * move_speed);
    if (keycode == KEY_S)
        move_player(game, -game->player.dir_x * move_speed, -game->player.dir_y * move_speed);
        
    // Strafe left/right
    if (keycode == KEY_A)
        move_player(game, game->player.dir_y * move_speed, -game->player.dir_x * move_speed); // Perpendicular vector
    if (keycode == KEY_D)
        move_player(game, -game->player.dir_y * move_speed, game->player.dir_x * move_speed);
        
    // Rotate
    if (keycode == KEY_LEFT)
        rotate_player(game, -rot_speed);
    if (keycode == KEY_RIGHT)
        rotate_player(game, rot_speed);
    
    return (0);
}
