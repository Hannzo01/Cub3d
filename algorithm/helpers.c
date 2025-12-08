/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:21:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/28 14:17:56 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d2.h"
#include <stdlib.h>
#include <string.h>

// Weak attribute allows these to be overridden by the main project if they exist there
__attribute__((weak)) void *gc_malloc(int size, t_map *game)
{
    (void)game;
    return malloc(size);
}

// Wrapper for memset
__attribute__((weak)) void *ft_memset(void *b, int c, size_t len)
{
    unsigned char *ptr = (unsigned char *)b;
    while (len-- > 0)
        *ptr++ = (unsigned char)c;
    return (b);
}
