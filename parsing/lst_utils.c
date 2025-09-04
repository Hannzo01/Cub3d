#include "../include/cub3d.h"

t_list	*lst_new(char *line)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->line = ft_strdup(line);
	if (node->line == NULL)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	lstadd_back(t_list **lst, char *line)
{
	t_list	*current;
	t_list	*new;

	if (!lst || !line)
		return ;
	new = lst_new(line);
	if (new == NULL)
		return ;
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
	game->map_height = 0;
	game->max_len = 0;
	while (lst != NULL)
	{
		len = ft_strlen(lst->line);
		game->map_height++;
		if (len > game->max_len)
			game->max_len = len;
		lst = lst->next;
	}
}
