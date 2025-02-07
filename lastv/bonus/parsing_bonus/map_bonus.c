/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:38:03 by mizem             #+#    #+#             */
/*   Updated: 2025/01/20 22:03:32 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

int	map_counter(char *line)
{
	char	*ptr[1024];
	int		i;
	int		j;
	int count;
	int		fd;

	i = 0;
	j = 0;
	count = 0;
	fd = open(line, O_RDWR);
    while (1)
	{
		ptr[i] = get_next_line(fd);
		if (!ptr[i])
			break ;
		i++;
	}
	while (ptr[j] && map_finder(ptr[j]) == 0)
		j++;
	while (ptr[j])
	{
		count++;
		j++;
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
	j = map_counter(line);
	fd = open(line, O_RDONLY);
	game->map = malloc(sizeof(char *) * (j + 1));
	while (1 && j > 0)
	{
		str[i] = get_next_line(fd);
		if (map_finder(str[i]))
		{
			game->map[0] = ft_strdup(str[i]);
			i = 1;
			while (1)
			{
				game->map[i] = get_next_line(fd);
				if (!game->map[i])
				{
					game->map[i] = NULL;
					return ;
				}
				i++;
			}
		}
		i++;
	}
	game->map[i] = NULL;
}
