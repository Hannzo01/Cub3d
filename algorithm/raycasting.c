/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:21:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/28 14:17:56 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void set_player_direction_vectors(t_game *game)
{
    if (game->player.direction == 'N') {
        game->player.dir_x = 0.0;
        game->player.dir_y = -1.0;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0.0;
    }
    if (game->player.direction == 'S') {
        game->player.dir_x = 0.0;
        game->player.dir_y = 1.0;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0.0;
    }
    if (game->player.direction == 'W') {
        game->player.dir_x = -1.0;
        game->player.dir_y = 0.0;
        game->player.plane_x = 0.0;
        game->player.plane_y = -0.66;
    }
    if (game->player.direction == 'E') {
        game->player.dir_x = 1.0;
        game->player.dir_y = 0.0;
        game->player.plane_x = 0.0;
        game->player.plane_y = 0.66;
    }
}


