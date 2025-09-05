#include "../include/cub3d.h"
#include <string.h>


/*
Parsing rules:
- Map must always be the last element (no params after it).
- Map cannot contain empty lines (invalid).
- Parameters (NO, SO, WE, EA, F, C) can appear in any order.
- Parameters can be separated by one or more empty lines.
- Parameters can have multiple spaces between type and value.
*/


int	check_path_validity_fill(char *line)
{
	//check if path is valid
	char *found;

	found = ft_strchr(line, '.');
	{

		//fill the struct
	}
	// return -1 if invalid
}


int	check_if_metabeta(char *line)
{
	if (strncmp(line, "NO", 2) == 0)
		if (check_path_validity_fill(line) == 0)
			return (1);
	else if(strncmp(line, "SO", 2) == 0)

	else if(strncmp(line, "WE", 2) == 0)

	else if(strncmp(line, "EA", 2) == 0)

	else if(strncmp(line, "F", 1) == 0)

	else if(strncmp(line, "C", 1) == 0)

	return (-1);
}

void read_map(char *filename, t_list **lst, t_map_info *map_info)
{
    int		fd;
    char	*line;
    char	*ptr;

	fd = open(filename, O_RDONLY);
    if (fd < 0)
        return;

    line = get_next_line(fd);
    while (line)
    {
		if (map_info->stop_trimming == 0)
		{
			ptr = line; // trim espace mn lwl
			while (*ptr == ' ' || *ptr == '\t')
				ptr++;
			if (*ptr != '\0' && *ptr != '\n')
			{
				if (check_if_metabeta(ptr) == -1)
					//invalid
					// return ;
			}
		}
		else if (map_info->stop_trimming == 1)
		{
			lstadd_back(lst, ft_strdup(line));

		}
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
}


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
		printf("----%d------\n", ft_strlen(map[i]));
        printf("%s", map[i]);
        i++;
    }
}

// void read_map(char *filename, t_list **lst)
// {
//     int fd;
//     char *line;
//     char *ptr;

//     fd = open(filename, O_RDONLY);
//     if (fd < 0)
//         return;

//     line = get_next_line(fd);
//     while (line)
//     {
//         ptr = line; // trim espace mn lwl
// 		while (*ptr == ' ' || *ptr == '\t')
// 			ptr++;
// 		if (*ptr != '\0' && *ptr != '\n')
// 			lstadd_back(lst, ft_strdup(ptr));
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);
// }

// void	read_map(char *map, t_list **lst)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open(map, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (line !)
// 			lstadd_back(lst, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }