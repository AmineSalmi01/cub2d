/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:20:10 by mizem             #+#    #+#             */
/*   Updated: 2025/01/21 23:30:08 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int floor_color_check(t_game *game)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (game->floor_color[i])
	{
		if (game->floor_color[i] == ',')
			flag++;
		i++;
	}
	if (flag != 2)
		return (1);
	return (0);
}
int floor_color_check_2(t_game *game)
{
	int i;
	int j;
	int flag;
	char **ptr;

	i = 0;
	flag = 0;
	ptr = ft_split(game->floor_color, ",\n");
	while (ptr[i])
	{
		j = 0;
		if (ft_atoi(ptr[i]) < 0 || ft_atoi(ptr[i]) > 255 || ft_strlen(ptr[i]) > 3)
			return (1);
		while (ptr[i][j])
		{
			if (ft_isdigit(ptr[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	ft_free(ptr);
	return (0);
}
int ceiling_color_check(t_game *game)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (game->ceiling_color[i])
	{
		if (game->ceiling_color[i] == ',')
			flag++;
		i++;
	}
	if (flag != 2)
		return (1);
	return (0);
}
int ceiling_color_check_2(t_game *game)
{
	int i;
	int j;
	int flag;
	char **ptr;

	i = 0;
	flag = 0;
	ptr = ft_split(game->ceiling_color, ",\n");
	while (ptr[i])
	{
		j = 0;
		if (ft_atoi(ptr[i]) < 0 || ft_atoi(ptr[i]) > 255 || ft_strlen(ptr[i]) > 3)
			return (1);
		while (ptr[i][j])
		{
			if (ft_isdigit(ptr[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	ft_free(ptr);
	return (0);
}
