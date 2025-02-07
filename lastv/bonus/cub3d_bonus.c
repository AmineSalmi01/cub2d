/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:51:46 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/21 21:31:57 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void rebuild_game(t_game *game)
{
	mlx_delete_image(game->mlx, game->image);
	draw_background(game);
	// draw_wall(game);
	// draw_player(game);
	cast_rays(game);
	// draw_line(game);
}

void ft_raycasting(t_game *game)
{
	draw_background(game);
	find_player(game);
	// draw_wall(game);
	// draw_player(game);
	cast_rays(game);
	// draw_line(game);
}

int main(int ac, char **av)
{
	t_game *game;

	if (ac != 2)
		return (1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	init_struct(game);
	parsing(game, av[1]);
	ft_raycasting(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
