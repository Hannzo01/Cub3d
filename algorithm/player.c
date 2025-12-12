/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:05:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/12 11:57:46 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// #define PLAYER_SIZE 8

// int is_wall_pixel(t_game *game, double new_x, double new_y) // check elach khask tkhdem b hado o mchi b lokhra
// {
//     int top_left_x;
//     int top_left_y;
//     int top_right_x;
//     int top_right_y;
//     int bottom_left_x;
//     int bottom_left_y;
//     int bottom_right_x;
//     int bottom_right_y;

//     top_left_x = (int)(new_x / TILE_SIZE);
//     top_left_y = (int)(new_y / TILE_SIZE);
//     top_right_x = (int)((new_x + PLAYER_SIZE) / TILE_SIZE);
//     top_right_y = (int)(new_y / TILE_SIZE);
//     bottom_left_x = (int)(new_x / TILE_SIZE);
//     bottom_left_y = (int)((new_y + PLAYER_SIZE) / TILE_SIZE);
//     bottom_right_x = (int)((new_x + PLAYER_SIZE) / TILE_SIZE);
//     bottom_right_y = (int)((new_y + PLAYER_SIZE) / TILE_SIZE);
//     if (top_left_x < 0 || top_left_y < 0 || bottom_right_x >= game->map.width
// 	|| bottom_right_y >= game->map.height)
//         return (1);
//     if (game->map.layout[top_left_y][top_left_x] == '1')
//         return (1);
//     if (game->map.layout[top_right_y][top_right_x] == '1')
//         return (1);
//     if (game->map.layout[bottom_left_y][bottom_left_x] == '1')
//         return (1);
//     if (game->map.layout[bottom_right_y][bottom_right_x] == '1')
//         return (1);
//     return (0);
// }

int	is_wall_pixel(t_game *game, int x, int y) // it checks only on corner which is wrong (I GUESS)
	{
		int map_x;
		int map_y;

		map_x = (int)(x / TILE_SIZE);
		map_y = (int)(y / TILE_SIZE);
		if (map_y < 0 || map_y >= game->map.height || map_x < 0
			|| map_x >= game->map.width)
			return (1);
		if (game->map.layout[map_y][map_x] == '1')
			return (1);
		return (0);
	}

	static void rotate_player(t_game *game, double angle)
	{
		double old_dir_x;
		double old_plane_x;
		double cos_rot;
		double sin_rot;

		old_dir_x = game->player.dir_x;
		old_plane_x = game->player.plane_x;
		cos_rot = cos(angle);
		sin_rot = sin(angle);
		game->player.dir_x = old_dir_x * cos_rot - game->player.dir_y * sin_rot;
		game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
		game->player.plane_x = old_plane_x * cos_rot - game->player.plane_y
			* sin_rot;
		game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y
			* cos_rot;
	}

	static void handle_rotation(t_game *game, int key)
	{
		if (key == RIGHT_KEY)
			rotate_player(game, ROT_SPEED);
		else if (key == LEFT_KEY)
			rotate_player(game, -ROT_SPEED);
	}

	static void calculate_new_position(t_game *game, int key, double *new_x,
		double *new_y)
	{
		if (key == W_KEY || key == UP_KEY)
		{
			*new_x += MOVE_SPEED * game->player.dir_x;
			*new_y += MOVE_SPEED * game->player.dir_y;
		}
		else if (key == S_KEY || key == DOWN_KEY)
		{
			*new_x -= MOVE_SPEED * game->player.dir_x;
			*new_y -= MOVE_SPEED * game->player.dir_y;
		}
		else if (key == D_KEY)
		{
			*new_x -= MOVE_SPEED * game->player.dir_y;
			*new_y += MOVE_SPEED * game->player.dir_x;
		}
		else if (key == A_KEY)
		{
			*new_x += MOVE_SPEED * game->player.dir_y;
			*new_y -= MOVE_SPEED * game->player.dir_x;
		}
	}

	int player_movment(int key, void *arg)
	{
		double new_x;
		double new_y;
		t_game *game;

		game = (t_game *)arg;
		if (key == ESC_KEY)
			print_error_and_exit(NULL, game->data);
		if (key == RIGHT_KEY || key == LEFT_KEY)
		{
			handle_rotation(game, key);
			return (key);
		}
		new_x = game->player.pos_x;
		new_y = game->player.pos_y;
		calculate_new_position(game, key, &new_x, &new_y);
		if (!is_wall_pixel(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (!is_wall_pixel(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
		return (key);
	}
