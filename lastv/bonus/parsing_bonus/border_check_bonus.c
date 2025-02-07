/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_check_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:35:24 by mizem             #+#    #+#             */
/*   Updated: 2025/01/20 22:03:20 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int checker(t_game *game, int x, int y)
{
	if (game->map[y][x + 1] == ' ' || game->map[y][x + 1] == '\n' || game->map[y][x + 1] == '\0')
		return (1);
	if (game->map[y][x - 1] == ' ' || game->map[y][x - 1] == '\n' || game->map[y][x - 1] == '\0')
		return (1);
	if (game->map[y - 1][x] == ' ' || game->map[y - 1][x] == '\n' || game->map[y - 1][x] == '\0')
		return (1);
	if (game->map[y + 1][x] == ' ' || game->map[y + 1][x] == '\n' || game->map[y + 1][x] == '\0')
		return (1);
	return (0);
}
int checker_2(t_game *game)
{
	int x;
	int y;

	y = 0;
	// while(game->map[y])
	// {
	// 	printf(">>%s", game->map[y]);
	// 	y++;
	// }
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (y == game->height - 1 && game->map[y - 1][0] == '\n')
				return (1);
			x++;
	    }
		y++;
	}
	return (0);
}
int border_check(t_game *game, int y, int x)
{
	if (y == 0)
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == '0' || game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'W' || game->map[y][x] == 'E')
				return (1);
			x++;
		}
	}
	if (x == 0 && (game->map[y][x] == '0' || game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'W' || game->map[y][x] == 'E'))
		return (1);
	if (y == game->height - 1)
	{
		while (game->map[y][x])
		{
			if ((game->map[y][x] == '0' || game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'W' || game->map[y][x] == 'E'))
				return (1);
			x++;
		}
	}
	if (((game->map[y][x] == '0' || game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'W' || game->map[y][x] == 'E')) && checker(game, x, y) == 1)
		return (1);
	return (0);
}
int map_checker(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '1' && game->map[y][x] != '0' && game->map[y][x] != 'N' && game->map[y][x] != 'S' 
				&& game->map[y][x] != 'W' && game->map[y][x] != 'E' && game->map[y][x] != ' ' && game->map[y][x] != '\n')
				return (1);
			x++;
	    }
		y++;
	}
	return (0);
}
int map_checker_2(t_game *game)
{
	int x;
	int y;
	int flag;

	y = 0;
	flag = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N')
				flag++;
			if (game->map[y][x] == 'S')
				flag++;
			if (game->map[y][x] == 'W')
				flag++;
			if (game->map[y][x] == 'E')
				flag++;
			x++;
	    }
		y++;
	}
	if (flag != 1)
		return (1);
	return (0);
}
int	borders(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	if (checker_2(game) == 1)
		return (1);
	if ( map_checker(game) == 1)
		return (1);
	if ( map_checker_2(game) == 1)
		return (1);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (border_check(game, y, x) == 1)
				return (1);
			x++;
	    }
		y++;
    }
    return (0);
}
