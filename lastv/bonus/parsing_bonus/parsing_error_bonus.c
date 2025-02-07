/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:38:35 by mizem             #+#    #+#             */
/*   Updated: 2025/01/20 22:03:44 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	file_check(char *name)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (name[i])
	{
		if (name[i] == '.')
		{
			count += 1;
            if (name[i + 1] != 'c' || name[i + 2] != 'u' 
                || name[i + 3] != 'b' || name[i + 4] != '\0')
                return (1);
		}
		i++;
	}
	if (count != 1)
        return (1);
	return (0);
}

int parsing_error(t_game *game)
{
    if (!game->map[0] || !game->elements[0] || borders(game) == 1)
        return (1);
    if (ft_strlen(game->trash))
        return (1);
    return (0);
}