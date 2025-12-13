/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:12 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/13 11:27:30 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_file_name(char *name, t_map *game)
{
	char	*dot;

	if (ft_strlen(name) < 5)
		print_error_and_exit("Error\nInvalid file name\n", game);
	dot = ft_strrchr(name, '.');
	if (dot == NULL)
		print_error_and_exit("Error\nInvalid file name\n", game);
	if (ft_strcmp(dot, ".cub") != 0)
		print_error_and_exit("Error\nInvalid extension. Usage: .cub\n", game);
	if (dot == name || *(dot - 1) == '/')
		print_error_and_exit("Error\nInvalid file name\n", game);
}
