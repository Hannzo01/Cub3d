/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:21 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 18:40:49 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	char_validity(char *rgb, t_map *game)
{
	int	counter;

	counter = 0;
	if (!(*rgb >= '0' && *rgb <= '9'))
		print_error_and_exit("Error\nRGB contains invalid characters\n", game);
	while (*rgb != '\0')
	{
		if (!((*rgb >= '0' && *rgb <= '9') || *rgb == ','))
			print_error_and_exit("Error\nRGB contains invalid characters\n",
				game);
		if (*rgb == ',')
			counter++;
		rgb++;
	}
	rgb--;
	if (!(*rgb >= '0' && *rgb <= '9'))
		print_error_and_exit("Error\nRGB contains invalid characters\n", game);
	return (counter);
}

static void	fill_rgb_arr(char **tab, char *element, t_map *game)
{
	int	i;

	i = 0;
	if (ft_strcmp(element, "C") == 0)
	{
		while (tab[i] != NULL)
		{
			game->map_info->c[i] = ft_atoi(tab[i]);
			i++;
		}
	}
	else if (ft_strcmp(element, "F") == 0)
	{
		while (tab[i] != NULL)
		{
			game->map_info->f[i] = ft_atoi(tab[i]);
			i++;
		}
	}
}

char	*elemet_var(char *line, t_map *game)
{
	int	start;
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		len++;
		i++;
	}
	len++;
	return (ft_substr(line, start, len, game));
}

static void	valid_rgb(char *rgb, char *element, t_map *game)
{
	char	**part;
	int		i;

	i = 0;
	if (ft_strlen(rgb) > 12)
		print_error_and_exit("Error\nInvalid RGB format\n", game);
	if (char_validity(rgb, game) == 2)
	{
		part = ft_split(rgb, ',', game);
		while (part[i] != NULL)
		{
			if (!(ft_atoi(part[i]) >= 0 && ft_atoi(part[i]) <= 255))
				print_error_and_exit("Error\nRGB value out of range (0-255)\n",
					game);
			i++;
		}
		fill_rgb_arr(part, element, game);
	}
	else
		print_error_and_exit("Error\nInvalid RGB format\n", game);
}

void	check_and_fill_color(char *element, char *tab, t_map *game)
{
	char	*rgb;

	if (count_param(tab) == 2)
	{
		rgb = elemet_value(tab, game);
		valid_rgb(rgb, element, game);
	}
	else
		print_error_and_exit("Error\nInvalid colors config line\n", game);
}
