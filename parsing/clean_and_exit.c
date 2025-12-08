/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:18 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 18:05:19 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_node_to_gc(void *ptr, t_map *game)
{
	t_gc	*new_node;

	if (ptr == NULL)
		return ;
	new_node = malloc(sizeof(t_gc));
	if (new_node == NULL)
		return ;
	new_node->p = ptr;
	new_node->next = game->gc;
	game->gc = new_node;
}

void	*gc_malloc(int size, t_map *game)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	add_node_to_gc(ptr, game);
	return (ptr);
}

void	gc_free(t_gc *gc)
{
	t_gc	*tmp;

	while (gc != NULL)
	{
		tmp = gc;
		gc = gc->next;
		free(tmp->p);
		free(tmp);
	}
}

void	print_error_and_exit(char *msg, t_map *game)
{
	ft_putstr_fd(msg, 2);
	get_next_line(-1);
	gc_free(game->gc);
	game->gc = NULL;
	free(game);
	exit(1);
}
