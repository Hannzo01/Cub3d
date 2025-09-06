/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:06:03 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 20:46:50 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_array_format(t_map *game)
{
	int		i;

	i = 0;
	while (game->map[i])
	{
		while (game->map[i] && check_for_empty_line(game->map[i]) == -1)
			i++;
		while (game->map[i] && check_for_empty_line(game->map[i]) == 1)
			i++;
		while (game->map[i] && check_for_empty_line(game->map[i]) == -1)
			i++;
	}
	if (game->map[i] && check_for_empty_line(game->map[i]) == 1)
		return (-1);
	return (1);
}

void	validate_map(t_map *game)
{
	if (check_array_format(game) == -1)
		print_error_and_exit("Error\nInvalid map\n", game);
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
