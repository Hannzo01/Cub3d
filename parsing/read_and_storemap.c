/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_storemap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:48 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/13 03:11:09 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int cheking(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == 0)
		return 1;
	return -1;
}

void	read_map(char *filename, t_list **lst, t_map *game)
{
	int		fd;
	char	*line;
	int		len;
	char	*line_gc;

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
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		{
			line[len - 1] = '\0';
			len--;
		}
		is_fully_filled(game);
		// if (line[ft_strlen(line) - 1] == '\n')
		// 	line[ft_strlen(line) - 1] = '\0';
		if (game->map_info->is_full == 0)
		{
			if (line[0] != '\0') // lamknch empty
				check_if_metabeta(line, game);
		}
		if (game->map_info->is_full == 1) // need to change its place
		{
			are_floor_and_ceiling_diff(game);
			lstadd_back(lst, f_strdup(line, game), game);
		}
		line = get_next_line(fd);
	}
	// said_check(lst);
	t_list *tmp = *lst;
	while (tmp && cheking(tmp->line) == 1)
	{
		*lst = tmp->next;
		tmp = tmp->next;
	}
	tmp = *lst;
	t_list *aps = NULL;
	while (tmp && cheking(tmp->line) == -1)
	{
		aps = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{		
		while (tmp && cheking(tmp->line) == 1)
		{
			aps->next = aps->next->next;
			tmp = aps->next;
		}
		if (tmp)
		{
			printf("erroooooooor\n");
			exit(1);
		}
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
