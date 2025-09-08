/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:53 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 20:44:19 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fill_element(char *element, char *value, t_map *game)
{
	if (ft_strcmp(element, "NO") == 0)
	{
		if (game->map_info->no != NULL)
			print_error_and_exit("Error\nDuplicate element detected\n", game);
		game->map_info->no = f_strdup(value, game);
	}
	if (ft_strcmp(element, "SO") == 0)
	{
		if (game->map_info->so != NULL)
			print_error_and_exit("Error\nDuplicate element detected\n", game);
		game->map_info->so = f_strdup(value, game);
	}
	if (ft_strcmp(element, "WE") == 0)
	{
		if (game->map_info->we != NULL)
			print_error_and_exit("Error\nDuplicate element detected\n", game);
		game->map_info->we = f_strdup(value, game);
	}
	if (ft_strcmp(element, "EA") == 0)
	{
		if (game->map_info->ea != NULL)
			print_error_and_exit("Error\nDuplicate element detected\n", game);
		game->map_info->ea = f_strdup(value, game);
	}
}

void	file_existance(char *value, t_map *game)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
		print_error_and_exit("Error\nFailed to open the file\n", game);
	close(fd);
}

static void	is_a_xpm_file(char *line, t_map *game)
{
	char	*dot;

	if (ft_strlen(line) < 5)
		print_error_and_exit("Error\nInvalid file name\n", game);
	dot = ft_strrchr(line, '.');
	if (dot == NULL)
		print_error_and_exit("Error\nInvalid file name\n", game);
	if (ft_strcmp(dot, ".xpm") != 0)
		print_error_and_exit("Error\nInvalid extension Usage --.xpm--\n", game);
}

char	*elemet_value(char *line, t_map *game)
{
	int	start;
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
	{
		len++;
		i++;
	}
	return (ft_substr(line, start, len, game));
}

void	validate_and_fill_texture(char *element, char *line, t_map *game)
{
	char	*value;

	if (count_param(line) == 2)
	{
		value = elemet_value(line, game);
		is_a_xpm_file(value, game);
		// file_existance(value);
		fill_element(element, value, game);
	}
	else
		print_error_and_exit("Error\nInvalid texture config line\n", game);
}
