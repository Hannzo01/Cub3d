/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:31:42 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/07 19:53:57 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D2_H
# define CUB3D2_H

# include "/home/sechlahb/Desktop/minilibx-linux/mlx.h"

typedef struct s_camera
{
    int cam_x;
    int cam_y;
}t_camera;

typedef struct s_game
{
    char **map;
    int height;
    int length;
    void *mlx;
    void *window;
    void *img_north;
    void *img_south;
    void *img_west;
    void *img_east;
    int F[3];
    int C[3];
    t_camera *camera;
    
}   t_game;

/*--------------raycasting----------------*/
void algorithm(t_map *game);


#endif