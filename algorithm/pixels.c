
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

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int get_texture_pixel(t_img *tex, int x, int y)
{
    char *dst;

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
    return (*(unsigned int*)dst);
}