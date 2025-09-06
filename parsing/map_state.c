/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:46 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 20:47:34 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_param(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i] != '\0')
	{
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			counter++;
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			i++;
	}
	return (counter);
}

void	check_if_metabeta(char *line, t_map *game)
{
	char	*element;

	element = elemet_var(line, game);
	if (ft_strncmp(element, "NO ", 3) == 0)
		validate_and_fill_texture("NO", line, game);
	else if (ft_strncmp(element, "SO ", 3) == 0)
		validate_and_fill_texture("SO", line, game);
	else if (ft_strncmp(element, "WE ", 3) == 0)
		validate_and_fill_texture("WE", line, game);
	else if (ft_strncmp(element, "EA ", 3) == 0)
		validate_and_fill_texture("EA", line, game);
	else if (ft_strncmp(element, "F ", 2) == 0)
		check_and_fill_color("F", line, game);
	else if (ft_strncmp(element, "C ", 2) == 0)
		check_and_fill_color("C", line, game);
	else
		print_error_and_exit(\
			"Error\nMissing or Unrecognized element in config\n", game);
}

void	is_fully_filled(t_map *game)
{
	if (game->map_info->ea && game->map_info->no && game->map_info->so
		&& game->map_info->we && game->map_info->f[0] != -1
		&& game->map_info->f[1] != -1 && game->map_info->f[2] != -1
		&& game->map_info->c[0] != -1 && game->map_info->c[1] != -1
		&& game->map_info->c[2] != -1)
	{
		game->map_info->is_full = 1;
	}
}

void	are_floor_and_ceiling_diff(t_map *game)
{
	if (game->map_info->f[0] == game->map_info->c[0]
		&& game->map_info->f[1] == game->map_info->c[1]
		&& game->map_info->f[2] == game->map_info->c[2])
		print_error_and_exit("Error\nFloor and ceiling colors must \
			be different\n", game);
}
