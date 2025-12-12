/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:18 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/12 11:42:36 by kemzouri         ###   ########.fr       */
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

void	clean_mlx(t_game *game)
{
	if (game->map.no_texture.img != NULL)
		mlx_destroy_image(game->mlx, game->map.no_texture.img);
	if (game->map.so_texture.img != NULL)
		mlx_destroy_image(game->mlx, game->map.so_texture.img);
	if (game->map.ea_texture.img != NULL)
		mlx_destroy_image(game->mlx, game->map.ea_texture.img);
	if (game->map.we_texture.img != NULL)
		mlx_destroy_image(game->mlx, game->map.we_texture.img);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	print_error_and_exit(char *msg, t_map *game)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd("GAME OVER\n", 1);
	if (game->game_ptr != NULL)
		clean_mlx(game->game_ptr);
	get_next_line(-1);
	gc_free(game->gc);
	game->gc = NULL;
	free(game);
	if (msg)
		exit(1);
	exit(0);
}
