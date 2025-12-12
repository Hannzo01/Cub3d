/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:35:00 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/12 10:59:41 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static void	load_texture(t_game *game, t_img *tex, char *path)
{
	if (!path)
		print_error_and_exit("Error\ninvalid path\n", game->data);
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		print_error_and_exit("Error\nmlx failed\n", game->data);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
        print_error_and_exit("Error\nFailed to get texture address\n", game->data);
}

void	init_textures(t_game *game)
{
	// Load textures using paths stored in the xpm field
	load_texture(game, &game->map.no_texture, game->map.no_texture.xpm);
	load_texture(game, &game->map.so_texture, game->map.so_texture.xpm);
	load_texture(game, &game->map.we_texture, game->map.we_texture.xpm);
	load_texture(game, &game->map.ea_texture, game->map.ea_texture.xpm);
}
