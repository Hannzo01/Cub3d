/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:16 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 20:28:19 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	valid_chars(t_map *game)
{
	int	i;

	i = 0;
	while (game->map[i] != NULL)
	{
		if (is_valid_line(game->map[i], game) == -1)
			return (-1);
		i++;
	}
	if (game->p_found == 0)
		return (-1);
	return (1);
}

int	is_valid_line(char *str, t_map *game)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'E' || str[i] == 'W' || str[i] == 'S')
		{
			if (game->p_found == 1)
				return (-1);
			game->p_found = 1;
		}
		if (str[i] != 'N' && str[i] != 'E' && str[i] != 'W' && str[i] != 'S'
			&& str[i] != '0' && str[i] != '1' && str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

int	is_surrounded(t_map *game)
{
	int	i;

	i = 0;
	if (is_wall(game->map[0]) == 1 && is_wall(game->map[game->height - 1]) == 1)
	{
		while (game->map[i] != NULL)
		{
			if (!(game->map[i][0] == '1' || game->map[i][0] == ' ')
				|| !(game->map[i][game->max_len - 1] == '1'
					|| game->map[i][game->max_len - 1] == ' '))
				return (-1);
			i++;
		}
		return (1);
	}
	return (-1);
}

int	is_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

void	save_player_pos(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'E'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'S')
			{
				game->p_x = j;
				game->p_y = i;
			}
			j++;
		}
		i++;
	}
}
