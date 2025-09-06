/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_II.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:56 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 20:26:41 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res);
}

char	*ft_substr(char *s, int start, int len, t_map *game)
{
	int		i;
	int		leng;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (f_strdup("", game));
	i = 0;
	leng = ft_strlen(s) - start;
	if (leng >= len)
		leng = len;
	sub = gc_malloc((leng + 1), game);
	while (s[start] && i < leng)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*f_strdup(char *str, t_map *game)
{
	int		len;
	int		i;
	char	*p;

	i = 0;
	len = ft_stlen(str);
	p = gc_malloc(sizeof(char) * len + 1, game);
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

int	check_for_empty_line(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (-1);
}
