/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:26 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/08 19:14:15 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_game(t_map *game)
{
	int	i;

	i = 0;
	ft_memset(game, 0, sizeof(t_map));
	game->map_info = gc_malloc(sizeof(t_info), game);
	ft_memset(game->map_info, 0, sizeof(t_info));
	while (i < 3)
	{
		game->map_info->f[i] = -1;
		game->map_info->c[i] = -1;
		i++;
	}
}
