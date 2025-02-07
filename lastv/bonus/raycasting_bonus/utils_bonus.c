/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:45:21 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/20 22:04:10 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

size_t count_height(char **map)
{
	int size;

	size = 0;
	while (map[size])
		size++;
	return (size);
}

size_t count_width(char **map)
{
	int size_w;
	int size_h;
	int b_size;

	size_h = 0;
	b_size = 0;
	while (map[size_h])
	{
		size_w = 0;
		while (map[size_h][size_w])
			size_w++;
		if (b_size < size_w)
			b_size = size_w;
		size_h++;
	}
	return (b_size);
}

double normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

bool is_wall(t_game *game, double x, double y)
{
	int x_tmp = floor(x / UNIT_SIZE);
	int y_tmp = floor(y / UNIT_SIZE);
	// printf("x_tmp: %d --- Width%d\n", x_tmp, game->width);
	// printf("y_tmp: %d--- height%d\n", y_tmp, game->height);
	if (x_tmp < 0 || y_tmp < 0 || x_tmp >= ft_strlen(game->map[y_tmp]) || y_tmp >= game->height)
		return (false);
	return (game->map[y_tmp][x_tmp] == '1');
}

double calculate_distance(double x1, double y1, double x2, double y2)
{
	double dx;
	double dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt((dx * dx) + (dy * dy)));
}
