#include "../include/cub3d.h"

int check_file_name(char *name)
{
	char *dot;
	if (ft_strlen(name) >= 5)
	{
		dot = ft_strrchr(name, '.');
		if (ft_strcmp(dot, ".cub") == 0)
			return (0);
	}
	return (1);
}
