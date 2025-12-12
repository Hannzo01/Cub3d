/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/05 17:07:55 by sechlahb         ###   ########.fr       */
/*                                                                              */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_img	*tex;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		ceil_c;
	int		tex_y;
	int		color;
	int		floor_c;

	// Prevent division by zero or extremely large heights
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	// Calculate height of line to draw on screen
	line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	// Calculate lowest and highest pixel to fill in current stripe
	draw_start = -line_height / 2 + SCREEN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_H / 2;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	// Determine texture based on wall direction
	if (ray->side == 0) // Vertical wall
		tex = (ray->step_x > 0) ? &game->map.we_texture : &game->map.ea_texture;
	else // Horizontal wall
		tex = (ray->step_y > 0) ? &game->map.no_texture : &game->map.so_texture;
	// Calculate wall_x (exact position of wall hit)
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	// Calculate texture x coordinate
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	// Calculate texture step
	step = 1.0 * tex->height / line_height;
	tex_pos = (draw_start - SCREEN_H / 2 + line_height / 2) * step;
	// Draw Ceiling
	ceil_c = create_trgb(0, game->map.ceil_color[0], game->map.ceil_color[1],
			game->map.ceil_color[2]);
	for (int y = 0; y < draw_start; y++)
		put_pixel(&game->screen, x, y, ceil_c);
	// Draw Wall with Texture
	for (int y = draw_start; y < draw_end; y++)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(&game->screen, x, y, color);
	}
	// Draw Floor
	floor_c = create_trgb(0, game->map.floor_color[0], game->map.floor_color[1],
			game->map.floor_color[2]);
	for (int y = draw_end; y < SCREEN_H; y++)
		put_pixel(&game->screen, x, y, floor_c);
}

// void draw_wall(t_game *game, t_ray *ray, int x)
// {
//     int line_height;
//     int draw_start;
//     int draw_end;

//     if (ray->perp_wall_dist < 0.0001)
//         ray->perp_wall_dist = 0.0001;
//     line_height = (int)(SCREEN_H / ray->perp_wall_dist);
//     draw_start = -line_height / 2 + SCREEN_H / 2;
//     if (draw_start < 0)
//         draw_start = 0;
//     draw_end = line_height / 2 + SCREEN_H / 2;
//     if (draw_end >= SCREEN_H)
//         draw_end = SCREEN_H - 1;

//     // shoud understand
//     int color;
//     if (ray->side == 0) // Vertical wall
//         color = (ray->step_x > 0) ? 0xEA2027 : 0x009432;
//     else // Horizontal wall
//         color = (ray->step_y > 0) ? 0x0652DD : 0xFFC312;

//     // Darken color for y-side walls to give depth
//     if (ray->side == 1)
//         color = (color >> 1) & 8355711;

//     // Draw Ceiling
//     int ceil_c = create_trgb(0, game->map.ceil_color[0],
//          game->map.ceil_color[1], game->map.ceil_color[2]);
//     for (int y = 0; y < draw_start; y++)
//         put_pixel(&game->screen, x, y, ceil_c);

//     // Draw Wall
//     for (int y = draw_start; y < draw_end; y++)
//         put_pixel(&game->screen, x, y, color);

//     // Draw Floor
//     int floor_c = create_trgb(0, game->map.floor_color[0],
//         game->map.floor_color[1], game->map.floor_color[2]);
//     for (int y = draw_end; y < SCREEN_H; y++)
//         put_pixel(&game->screen, x, y, floor_c);
// }

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->map.height || ray->map_y < 0
			|| ray->map_y >= game->map.width)
			hit = 1;
		if (game->map.layout[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	raycasting(t_game *game, int x)
{
	t_ray	ray;
	double	ray_angle;
	double	fov;

	fov = 60 * (M_PI / 180); // 60 degrees FOV
	game->player.angle = atan2(game->player.dir_y, game->player.dir_x);
	ray_angle = game->player.angle - (fov / 2) + (x * fov / SCREEN_W);
	ray.dir_x = cos(ray_angle);
	ray.dir_y = sin(ray_angle);
	ray.map_x = (int)(game->player.pos_x / TILE_SIZE);
	ray.map_y = (int)(game->player.pos_y / TILE_SIZE);
	if (ray.dir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = fabs(1 / ray.dir_x);
	if (ray.dir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = fabs(1 / ray.dir_y);
	if (ray.dir_x < 0)
	{
		ray.step_x = -1;
		ray.side_dist_x = (game->player.pos_x / TILE_SIZE - ray.map_x)
			* ray.delta_dist_x;
	}
	else
	{
		ray.step_x = 1;
		ray.side_dist_x = (ray.map_x + 1.0 - game->player.pos_x / TILE_SIZE)
			* ray.delta_dist_x;
	}
	if (ray.dir_y < 0)
	{
		ray.step_y = -1;
		ray.side_dist_y = (game->player.pos_y / TILE_SIZE - ray.map_y)
			* ray.delta_dist_y;
	}
	else
	{
		ray.step_y = 1;
		ray.side_dist_y = (ray.map_y + 1.0 - game->player.pos_y / TILE_SIZE)
			* ray.delta_dist_y;
	}
	perform_dda(game, &ray);
	ray.perp_wall_dist *= cos(ray_angle - game->player.angle);
	draw_wall(game, &ray, x);
}

int	rander_map(t_game *game)
{
	int i;

	i = 0;
	while (i < SCREEN_W)
	{
		raycasting(game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}