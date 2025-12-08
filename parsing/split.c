/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:51 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 18:05:52 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	counter;

	if (s == NULL)
		return (0);
	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			counter++;
		}
	}
	return (counter);
}

static char	*extract_word(char *s, char c, int *sep_pos, t_map *game)
{
	int		start;
	int		len;
	char	*word;

	while (s[*sep_pos] == c)
		(*sep_pos)++;
	start = *sep_pos;
	len = 0;
	while (s[*sep_pos] != c && s[*sep_pos] != '\0')
	{
		(*sep_pos)++;
		len++;
	}
	word = ft_substr(s, start, len, game);
	return (word);
}

char	**ft_split(char *s, char c, t_map *game)
{
	int		i;
	char	**p;
	int		counter;
	int		sep_pos;

	sep_pos = 0;
	counter = count_words(s, c);
	if (!s)
		return (NULL);
	p = gc_malloc((counter + 1) * sizeof(char *), game);
	i = 0;
	while (i < counter)
	{
		p[i] = extract_word(s, c, &sep_pos, game);
		i++;
	}
	p[i] = NULL;
	return (p);
}
