/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_storemap_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:48 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/08 20:43:15 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	read_map(char *filename, t_list **lst, t_map *game)
{
	int		fd;
	char	*line;
	int		len;
	char	*line_gc;
	int		map_started = 0; // set when first map line stored 
	int		map_ended = 0;   // tbdl mnin line yban mora matbda2 map
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_and_exit("Error\nFailed to open the file\n", game);
	line = get_next_line(fd);
	while (line)
	{

		line_gc = f_strdup(line, game);
		free(line);
		line = line_gc;

		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) //ft_strtrim from libft 
		{
			line[len - 1] = '\0';
			len--;
		}

		if (game->map_info->is_full == 0)
		{
			is_fully_filled(game);
			if (game->map_info->is_full == 0)
			{
				if (line[0] != '\0') // lamknch empty
					check_if_metabeta(line, game);
			}
		}
		if (game->map_info->is_full == 1) // map reading phase
		{
			if (line[0] == '\0')
			{
				// empty line after map started -> mark map ended
				if (map_started)
					map_ended = 1;
				// ;lmtch bdat map ra zed
			}
			else
			{
				if (map_ended)
					print_error_and_exit("Error\nContent after map", game);
				lstadd_back(lst, f_strdup(line, game), game);
				map_started = 1;
			}
		}
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1); // clean static var d gnl
}

void	allocate_and_fill_map(t_map *game, t_list *lst)
{
	int	i;
	int	j;

	i = 0;
	game->map = gc_malloc(sizeof(char *) * (game->height + 1), game);
	while (i < game->height)
	{
		game->map[i] = gc_malloc(sizeof(char) * (game->max_len + 1), game);
		ft_strcpy(game->map[i], lst->line);
		j = ft_strlen(lst->line);
		while (j < game->max_len)
		{
			game->map[i][j] = ' ';
			j++;
		}
		game->map[i][j] = '\0';
		i++;
		lst = lst->next;
	}
	game->map[i] = NULL;
}
