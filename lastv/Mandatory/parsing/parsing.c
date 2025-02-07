/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:51:46 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/27 20:43:52 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void parsing(t_game *game, char *line)
{
	if (file_check(line) == 1)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	elements(game, line);
	map(game, line);
	game->width = count_width(game->map);
	game->height = count_height(game->map);
	if (struct_elements(game) == 1 || parsing_error(game) == 1)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}
