/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:37:32 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/13 01:00:21 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	parsing(char *input, t_map *game, t_list **lst)
{
	check_file_name(input, game);
	read_map(input, lst, game);
	map_size(*lst, game);
	allocate_and_fill_map(game, *lst);
	validate_map(game);
	// printf("----PARSING IS DONE----\n");
}

int	main(int argc, char *argv[])
{
	t_list	*lst;
	t_map	*game;

	lst = NULL;
	game = malloc(sizeof(t_map));
	if (game == NULL)
		return (1);
	initialize_game(game);
	if (argc == 2)
	{
		parsing(argv[1], game, &lst);
		algorithm(game);
		gc_free(game->gc);
		game->gc = NULL;
		free(game);
	}
	else
		return (ft_putstr_fd("Enter a valid input\n", 2), 1);
	return (0);
}
