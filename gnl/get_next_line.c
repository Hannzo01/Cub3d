/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:59:32 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/06 16:55:21 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_one_line(int fd, char *store)
{
	char	*buf;
	ssize_t	rr;

	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		rr = read(fd, buf, BUFFER_SIZE);
		if (rr <= 0)
			break ;
		buf[rr] = '\0';
		store = handle_buffer(store, buf);
		if (!store || ft_strchr(store, '\n'))
			break ;
	}
	free(buf);
	if (rr < 0 || (rr == 0 && (store == NULL || *store == '\0')))
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	return (store);
}

static char	*remove_after_newline(char *store)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!store)
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		line[j] = store[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*get_remainder(char *store)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	j = 0;
	if (!store)
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	tmp = malloc((ft_stlen(store) - i + 1));
	if (!tmp)
		return (NULL);
	while (store[i])
	{
		tmp[j] = store[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(store);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd == -1)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	if (fd <= 0)
		return (NULL);
	store = get_one_line(fd, store);
	line = remove_after_newline(store);
	store = get_remainder(store);
	return (line);
}
