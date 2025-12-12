/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_storemap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:48 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/12 09:35:50 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_map_content(char *line, t_list **lst, t_map *game,
		int *state)
{
	if (line[0] == '\0')
	{
		if (state[0] == 1)
			state[1] = 1;
	}
	else
	{
		if (state[1] == 1)
			print_error_and_exit("Error\nContent after map\n", game);
		lstadd_back(lst, f_strdup(line, game), game);
		state[0] = 1;
	}
}

static void	process_line(char *line, t_list **lst, t_map *game, int *state)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	if (game->map_info->is_full == 0)
	{
		is_fully_filled(game);
		if (game->map_info->is_full == 0)
		{
			if (line[0] != '\0')
				check_if_metabeta(line, game);
		}
	}
	if (game->map_info->is_full == 1)
		handle_map_content(line, lst, game, state);
}

void	read_map(char *filename, t_list **lst, t_map *game)
{
	char	*line;
	char	*tmp;
	int		fd;
	int		state[2];

	state[0] = 0;
	state[1] = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_and_exit("Error\nFailed to open the file\n", game);
	line = get_next_line(fd);
	while (line)
	{
		tmp = f_strdup(line, game);
		free(line);
		process_line(tmp, lst, game, state);
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1);
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
