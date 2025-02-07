/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:31:53 by mizem             #+#    #+#             */
/*   Updated: 2025/01/27 20:40:21 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	doors_counter(t_game *game)
{
	int x;
	int	y;
	int c;

	y = 0;
	c = 0;
	while(game->map[y])
	{
		x = 0;
		while(game->map[y][x])
		{
			if (game->map[y][x] == 'C' || game->map[y][x] == 'O')
				c++;
			x++;
		}
		y++;
	}
	return (c);
}
int	elements_counter(char *line)
{
	char	*ptr;
    char    buffer[1024];
	int		i;
	int		j;
	int		fd;
	int		index;
    int     b_read;

	i = 0;
	j = 0;
	fd = open(line, O_RDWR);
    b_read = 1;
	index = 0;
    while (b_read > 0)
    {
        b_read = read(fd, &buffer[index], 1);
        if (b_read > 0 && buffer[index] == '\n')
        {
			j++;
            buffer[index + 1] = '\0';
            if (map_finder(buffer) == 1)
                return (j - 1);
            index = 0;
        }
        else
            index++;
    }
	return (j);
}

void	elements(t_game *game, char *line)
{
    int i;
	int j;
	int fd;

	i = 0;
	j = elements_counter(line);
	fd = open(line, O_RDWR);
	game->elements = malloc(sizeof(char *) * (j + 1));
	while (i < j)
	{
		game->elements[i] = get_next_line(fd);
		if (!game->elements[i] || map_finder(game->elements[i]) == 1)
			break ;
		i++;
	}
	game->elements[i] = NULL;
	close(fd);
}
int	struct_elements(t_game *game)
{
	int i;
	int flag;
	char **str;

	i = 0;
	flag = 0;
	if (!*(game->elements))
		return 1;
	while (game->elements[i])
	{
		str = ft_split(game->elements[i], " 	");
		if (ft_strcmp(str[0], "NO") == 0)
		{
			game->no_path = ft_strdup(str[1]);
			flag++;
		}
		else if (ft_strcmp(str[0], "SO") == 0)
		{
			game->so_path = ft_strdup(str[1]);
			flag++;
		}
		else if (ft_strcmp(str[0], "WE") == 0)
		{
			game->we_path = ft_strdup(str[1]);
			flag++;
		}
		else if (ft_strcmp(str[0], "EA") == 0)
		{
			game->ea_path = ft_strdup(str[1]);
			flag++;
		}
		else if (ft_strcmp(str[0], "F") == 0)
		{
			game->floor_color = ft_strdup(str[1]);
			flag++;
		}
		else if (ft_strcmp(str[0], "C") == 0)
		{
			game->ceiling_color = ft_strdup(str[1]);
			flag++;
		}
		else if (str && (str[0][0] >= 33 && str[0][0] <= 126))
			game->trash = ft_strdup(str[0]);
		i++;
		ft_free(str);
	}
	if (flag != 6)
		return (1);
	return (0);
}