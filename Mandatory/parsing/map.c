/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:38:03 by mizem             #+#    #+#             */
/*   Updated: 2025/01/27 20:41:43 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int map_finder(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '1')
			j++;
	    if (j >= 3)
		    return (1);
		i++;
	}
	return (0);
}

int	map_counter(char *line, char **str)
{
	char    buffer[1024];
	int		i;
	int		b_read;
	int		index;
	int 	count;
	int		fd;

	i = 0;
	b_read = 1;
	index = 0;
	count = 0;
	fd = open(line, O_RDWR);
	while (b_read > 0)
    {
        b_read = read(fd, &buffer[index], 1);
        if (b_read > 0 && buffer[index] == '\n')
        {
            buffer[index + 1] = '\0';
			str[i] = ft_strdup(buffer);
			i++;
            index = 0;
        }
        else
            index++;
    }
    if (index > 0)
    {
        buffer[index] = '\0';
        str[i] = ft_strdup(buffer);
        i++;
    }
    str[i] = NULL;
	i = 0;
	while (str[i] && map_finder(str[i]) == 0)
		i++;
	while (str[i])
	{
		count++;
		i++;
	}
	close(fd);	
	return (count);
}

void	map(t_game *game, char *line)
{
    int i;
	int j;
	int fd;
	char *str[1024];

	i = 0;
	j = map_counter(line, str);
	fd = open(line, O_RDONLY);
	game->map = malloc(sizeof(char *) * (j + 1));
	while (str[i] && map_finder(str[i]) == 0)
		i++;
	j = 0;
	while (1)
	{
		if (!str[i])
			break;
		game->map[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	game->map[j] = NULL;
}
