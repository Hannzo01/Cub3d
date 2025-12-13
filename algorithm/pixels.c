/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/05 17:07:55 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	int trgb;

	trgb = 0;
	trgb += t << 24;
	trgb += r << 16;
	trgb += g << 8;
	trgb += b;
	return trgb;
}

unsigned int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (!tex || !tex->addr)
		return (0);
	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static int	check_corner(t_game *game, int cx, int cy)
{
	int	map_x;
	int	map_y;

	map_x = (int)(cx / TILE_SIZE);
	map_y = (int)(cy / TILE_SIZE);
	if (map_y < 0 || map_y >= game->map.height || map_x < 0
		|| map_x >= game->map.width)
		return (1);
	return (game->map.layout[map_y][map_x] == '1');
}

int	is_wall_pixel(t_game *game, int x, int y)
{
	int	half;
	int	cx0;
	int	cx1;
	int	cy0;
	int	cy1;

	half = PLAYER_SIZE / 2;
	cx0 = x - half;
	cx1 = x + half;
	cy0 = y - half;
	cy1 = y + half;
	if (check_corner(game, cx0, cy0))
		return (1);
	if (check_corner(game, cx1, cy0))
		return (1);
	if (check_corner(game, cx0, cy1))
		return (1);
	if (check_corner(game, cx1, cy1))
		return (1);
	return (0);
}
