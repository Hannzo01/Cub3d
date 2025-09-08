/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/08 18:27:14 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game *fill_data(t_map *data)
{
    t_game *game;

    game = gc_malloc(sizeof(t_game), data);
    game->map = data->map;
    game->F = data->map_info->f;
    game->C = data->map_info->c;
    game->length = data->max_len;
    game->height = data->height;
    
}

void algorithm(t_map *data)
{
    t_game *game;

    game = fill_data(data);
    
}