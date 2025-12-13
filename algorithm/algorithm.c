/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/13 13:20:12 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fill_dir(t_game *game, char direction)
{
	double	angle;

	if (direction == 'N')
		angle = 3 * M_PI / 2;
	else if (direction == 'S')
		angle = M_PI / 2;
	else if (direction == 'W')
		angle = M_PI;
	else if (direction == 'E')
		angle = 0;
	game->player.dir_x = cos(angle);
	game->player.dir_y = sin(angle);
	game->player.plane_x = -sin(angle) * 0.66;
	game->player.plane_y = cos(angle) * 0.66;
}

static t_game	*fill_data(t_map *data)
{
	t_game	*game;

	game = gc_malloc(sizeof(t_game), data);
	ft_memset(game, 0, sizeof(t_game));
	game->data = data;
	data->game_ptr = game;
	game->map.layout = data->map;
	game->map.width = data->max_len;
	game->map.height = data->height;
	game->map.no_texture.xpm = data->map_info->no;
	game->map.so_texture.xpm = data->map_info->so;
	game->map.we_texture.xpm = data->map_info->we;
	game->map.ea_texture.xpm = data->map_info->ea;
	game->map.floor_color = data->map_info->f;
	game->map.ceil_color = data->map_info->c;
	game->player.pos_x = (double)data->p_x * TILE_SIZE + TILE_SIZE / 2.0;
	game->player.pos_y = (double)data->p_y * TILE_SIZE + TILE_SIZE / 2.0;
	fill_dir(game, game->map.layout[data->p_y][data->p_x]);
	game->map.layout[data->p_y][data->p_x] = '0';
	return (game);
}

int	handle_exit(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	print_error_and_exit(NULL, game->data);
	return (0);
}

void	algorithm(t_map *data)
{
	t_game	*game;

	game = fill_data(data);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		print_error_and_exit("Error\nMlx connection failed\n", data);
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (game->win == NULL)
		print_error_and_exit("Error\nMlx creating win failed\n", data);
	init_textures(game);
	game->screen.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp,
			&game->screen.line_len, &game->screen.endian);
	mlx_hook(game->win, 17, 0, handle_exit, game);
	mlx_hook(game->win, 2, 1L << 0, player_movment, game);
	mlx_loop_hook(game->mlx, rander_map, game);
	mlx_loop(game->mlx);
}
