/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_strchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:54:51 by mizem             #+#    #+#             */
/*   Updated: 2025/01/20 22:05:01 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	ft_mini_strchr(char s, char *c)
{
	int y;

	y = 0;
	while (c[y])
	{
		if (s == c[y])
			return (1);
		y++;
	}
	return (0);
}
int     ft_strcmp(char *s1, char *s2)
{
        int     i;

        i = 0;
        while ((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0')
        {
                if ((unsigned char)s1[i] != (unsigned char)s2[i])
                        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
                i++;
        }
        return (0);
}
