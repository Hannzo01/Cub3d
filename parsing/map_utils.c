#include "../include/cub3d.h"

void read_map(char *filename, t_list **lst)
{
    int fd;
    char *line;
    char *ptr;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return;

    line = get_next_line(fd);
    while (line)
    {
        ptr = line; // trim esppace mn lwl
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (*ptr != '\0' && *ptr != '\n')
			lstadd_back(lst, ft_strdup(ptr));
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
}


// void	read_map(char *map, t_list **lst)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open(map, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		lstadd_back(lst, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }

void allocate_and_fill_map(t_map *game, t_list *lst)
{
	int		i;
	int		j;

	i = 0;
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (game->map == NULL)
        return ;
	while (i < game->map_height)
	{
		game->map[i] = malloc(sizeof(char) * (game->max_len + 1));
		if (game->map == NULL)
			return ;
		ft_strcpy(game->map[i], lst->line);
		j = ft_strlen(lst->line);
		while (j < game->max_len)
		{
			game->map[i][j] = ' ';
			j++;
		}
		game->map[i][j] = '\0';
		i++;
		lst = lst->next;
	}
	game->map[i] = NULL;
}

void print_map(char **map)
{
    int i = 0;
    while (map[i])
    {
        printf("%s", map[i]);
        i++;
    }
}
