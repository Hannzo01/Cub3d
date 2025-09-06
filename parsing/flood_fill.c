/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:34 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 18:05:35 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	copy_map(t_map *game)
{
	int	i;

	i = 0;
	game->clone_map = gc_malloc(sizeof(char *) * (game->height + 1), game);
	while (i < game->height)
	{
		game->clone_map[i] = f_strdup(game->map[i], game);
		i++;
	}
	game->clone_map[i] = NULL;
}

void	flood_fill(t_map *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->max_len || y >= game->height)
		return ;
	if (game->clone_map[y][x] == ' ')
	{
		game->invalid = 1;
		return ;
	}
	if (game->clone_map[y][x] == 'V' || game->clone_map[y][x] == '1')
		return ;
	game->clone_map[y][x] = 'V';
	flood_fill(game, x - 1, y);
	flood_fill(game, x + 1, y);
	flood_fill(game, x, y - 1);
	flood_fill(game, x, y + 1);
}
