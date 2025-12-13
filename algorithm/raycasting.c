/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/13 20:36:26 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_ray(t_game *game, t_ray *ray, int x, double *ray_angle)
{
	double	fov;

	fov = 60 * (M_PI / 180);
	game->player.angle = atan2(game->player.dir_y, game->player.dir_x);
	*ray_angle = game->player.angle - (fov / 2) + (x * fov / SCREEN_W);
	ray->dir_x = cos(*ray_angle);
	ray->dir_y = sin(*ray_angle);
	ray->map_x = (int)(game->player.pos_x / TILE_SIZE);
	ray->map_y = (int)(game->player.pos_y / TILE_SIZE);
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	compute_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x / TILE_SIZE - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x / TILE_SIZE)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y / TILE_SIZE - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y / TILE_SIZE)
			* ray->delta_dist_y;
	}
}

void	raycasting(t_game *game, int x)
{
	t_ray	ray;
	double	ray_angle;

	init_ray(game, &ray, x, &ray_angle);
	compute_step_and_side(game, &ray);
	perform_dda(game, &ray);
	ray.perp_wall_dist *= cos(ray_angle - game->player.angle);
	draw_wall(game, &ray, x);
}

int	rander_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < SCREEN_W)
	{
		raycasting(game, i);
		i++;
	}
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}
