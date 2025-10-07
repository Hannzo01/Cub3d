/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:05:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/10/04 16:07:25 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int player_movment(int key, void *arg)
{
    t_game *game;

    game = (t_game *)arg;
    if (esc == key)
        exit (0);
    if (w_key == key)
        game->player.up = 1;
    if (a_key == key)
        game->player.left = 1;
    if (s_key == key)
        game->player.down = 1;
    if (d_key == key)
        game->player.right = 1;

    // if (up_key == key)
    //     game->player.up = 1;
    // if (left_key == key)
    //     game->player.left = 1;
    // if (down_key == key)
    //     game->player.down = 1;
    // if (right_key == key)
    //     game->player.right = 1;
    rander_map((t_game *)arg);
    return key;
}