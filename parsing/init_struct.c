/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:26 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 20:28:43 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_game(t_map *game)
{
	int	i;

	i = 0;
	game->p_found = 0;
	game->p_x = 0;
	game->p_y = 0;
	game->invalid = 0;
	game->height = 0;
	game->max_len = 0;
	game->clone_map = NULL;
	game->map = NULL;
	game->gc = NULL;
	game->map_info = gc_malloc(sizeof(t_info), game);
	game->map_info->no = NULL;
	game->map_info->so = NULL;
	game->map_info->we = NULL;
	game->map_info->ea = NULL;
	game->map_info->is_full = 0;
	while (i < 3)
	{
		game->map_info->f[i] = -1;
		game->map_info->c[i] = -1;
		i++;
	}
}
