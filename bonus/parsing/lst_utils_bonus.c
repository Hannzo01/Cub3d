/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:05:40 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/08 20:43:23 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_list	*lst_new(char *line, t_map *game)
{
	t_list	*node;

	node = gc_malloc(sizeof(t_list), game);
	node->line = f_strdup(line, game);
	node->next = NULL;
	return (node);
}

void	lstadd_back(t_list **lst, char *line, t_map *game)
{
	t_list	*current;
	t_list	*new;

	if (!lst || !line)
		return ;
	new = lst_new(line, game);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	map_size(t_list *lst, t_map *game)
{
	int	len;

	while (lst != NULL)
	{
		len = ft_strlen(lst->line);
		game->height++;
		if (len > game->max_len)
			game->max_len = len;
		lst = lst->next;
	}
}
