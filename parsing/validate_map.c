/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:06:03 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/12 09:35:38 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_map(t_map *game)
{
	if (valid_chars(game) == -1)
		print_error_and_exit("Error\nInvalid Characters\n", game);
	if (is_surrounded(game) == -1)
		print_error_and_exit("Error\nMap not surrounded by walls\n", game);
	save_player_pos(game);
	copy_map(game);
	flood_fill(game, game->p_x, game->p_y);
	if (game->invalid == 1)
		print_error_and_exit("Error\nFlood fill detected an open map\n", game);
}
