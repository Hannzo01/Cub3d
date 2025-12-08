/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:21:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/12/08 22:17:55 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void perform_dda(t_game *game, t_ray *ray)
{
    int hit = 0;
    
    while (hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // Hit a vertical line (x-side)
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // Hit a horizontal line (y-side)
        }
        
        // Check bounds
        if (ray->map_y < 0 || ray->map_y >= game->map.height ||
            ray->map_x < 0 || ray->map_x >= game->map.width)
        {
            hit = 1;
        }
        // Check wall
        else if (game->map.layout[ray->map_y][ray->map_x] == '1')
        {
            hit = 1;
        }
    }
    
    // Calculate perpendicular distance to avoid fisheye effect
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void cast_ray(t_game *game, int x)
{
    t_ray ray;
    
    // Calculate ray position and direction
    double camera_x = 2 * x / (double)SCREEN_W - 1; // x-coordinate in camera space
    ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;
    
    // Which box of the map we're in
    ray.map_x = (int)(game->player.pos_x / TILE_SIZE);
    ray.map_y = (int)(game->player.pos_y / TILE_SIZE);
    
    // Length of ray from one x or y-side to next x or y-side
    ray.delta_dist_x = (ray.dir_x == 0) ? 1e30 : fabs(1 / ray.dir_x);
    ray.delta_dist_y = (ray.dir_y == 0) ? 1e30 : fabs(1 / ray.dir_y);
    
    // Calculate step and initial sideDist
    if (ray.dir_x < 0)
    {
        ray.step_x = -1;
        ray.side_dist_x = (game->player.pos_x / TILE_SIZE - ray.map_x) * ray.delta_dist_x;
    }
    else
    {
        ray.step_x = 1;
        ray.side_dist_x = (ray.map_x + 1.0 - game->player.pos_x / TILE_SIZE) * ray.delta_dist_x;
    }
    
    if (ray.dir_y < 0)
    {
        ray.step_y = -1;
        ray.side_dist_y = (game->player.pos_y / TILE_SIZE - ray.map_y) * ray.delta_dist_y;
    }
    else
    {
        ray.step_y = 1;
        ray.side_dist_y = (ray.map_y + 1.0 - game->player.pos_y / TILE_SIZE) * ray.delta_dist_y;
    }
    
    perform_dda(game, &ray);
    draw_wall(game, &ray, x);
}
