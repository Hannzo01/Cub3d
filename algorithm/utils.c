/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:21:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/28 14:17:56 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d2.h"
#include "../include/cub3d.h"
#include <stdlib.h>
#include <string.h>

void *gc_malloc(int size, t_map *game)
{
    (void)game;
    return malloc(size);
}

void *ft_memset(void *b, int c, size_t len)
{
    return memset(b, c, len);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    write(2, "Error\nThis is a test build. Please link with full project.\n", 59);
    return (1);
}
