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

static void	compute_line_params(t_ray *ray, int *line_height, int *draw_start,
		int *draw_end)
{
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	*line_height = (int)((SCREEN_H / ray->perp_wall_dist) + 0.5);
	*draw_start = SCREEN_H / 2 - *line_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = SCREEN_H / 2 + *line_height / 2 - 1;
	if (*draw_end >= SCREEN_H)
		*draw_end = SCREEN_H - 1;
}

static void	select_texture_and_wallx(t_game *game, t_ray *ray, t_img **tex,
		double *wall_x)
{
	if (ray->side == 1)
	{
		if (ray->step_y < 0)
			*tex = &game->map.we_texture;
		else
			*tex = &game->map.ea_texture;
	}
	else
	{
		if (ray->step_x < 0)
			*tex = &game->map.no_texture;
		else
			*tex = &game->map.so_texture;
	}
	if (ray->side == 0)
		*wall_x = (game->player.pos_y / (double)TILE_SIZE) + ray->perp_wall_dist
			* ray->dir_y;
	else
		*wall_x = (game->player.pos_x / (double)TILE_SIZE) + ray->perp_wall_dist
			* ray->dir_x;
	*wall_x -= floor(*wall_x);
}

static void	draw_textured_wall(t_game *game, t_tex_ctx *ctx)
{
	int	tex_y;
	int	color;
	int	y;

	y = ctx->draw_start;
	while (y <= ctx->draw_end)
	{
		tex_y = (int)ctx->pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ctx->tex->height)
			tex_y = ctx->tex->height - 1;
		ctx->pos += ctx->step;
		color = get_texture_pixel(ctx->tex, ctx->tx, tex_y);
		put_pixel(&game->screen, ctx->x, y, color);
		y++;
	}
}

static void	draw_ceiling_and_floor(t_game *game, int x, int draw_start,
		int draw_end)
{
	int	ceil_c;
	int	floor_c;
	int	y;

	ceil_c = create_trgb(0, game->map.ceil_color[0], game->map.ceil_color[1],
			game->map.ceil_color[2]);
	y = 0;
	while (y < draw_start)
	{
		put_pixel(&game->screen, x, y, ceil_c);
		y++;
	}
	floor_c = create_trgb(0, game->map.floor_color[0], game->map.floor_color[1],
			game->map.floor_color[2]);
	y = draw_end + 1;
	while (y < SCREEN_H)
	{
		put_pixel(&game->screen, x, y, floor_c);
		y++;
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_img		*tex;
	t_tex_ctx	ctx;

	compute_line_params(ray, &line_height, &draw_start, &draw_end);
	select_texture_and_wallx(game, ray, &tex, &ctx.pos);
	ctx.tex = tex;
	ctx.draw_start = draw_start;
	ctx.draw_end = draw_end;
	ctx.x = x;
	ctx.tx = (int)(ctx.pos * (double)tex->width);
	if (ray->side == 1 && ray->step_y > 0)
		ctx.tx = tex->width - ctx.tx - 1;
	if (ray->side == 0 && ray->step_x < 0)
		ctx.tx = tex->width - ctx.tx - 1;
	if (ctx.tx < 0)
		ctx.tx = 0;
	if (ctx.tx >= tex->width)
		ctx.tx = tex->width - 1;
	ctx.step = 1.0 * tex->height / line_height;
	ctx.pos = (draw_start - SCREEN_H / 2 + line_height / 2) * ctx.step;
	draw_ceiling_and_floor(game, x, draw_start, draw_end);
	draw_textured_wall(game, &ctx);
}
