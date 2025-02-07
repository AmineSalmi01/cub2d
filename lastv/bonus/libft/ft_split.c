/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:19:21 by mizem             #+#    #+#             */
/*   Updated: 2025/01/20 22:04:54 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int      words_nbr(char *s, char *c)
{
    int     i;
    int     nbr;

    i = 0;
    nbr = 0;
    while (s[i])
    {
        while (ft_mini_strchr(s[i], c) && s[i])
            i++;
    	if (!s[i])
            return (nbr);
		while (s[i] && !ft_mini_strchr(s[i], c))
        	i++;
        nbr++;
    }
    return (nbr);
}

int      letters_nbr(char *s, char *c)
{
        int     i;

        i = 0;
        while (!ft_mini_strchr(s[i], c) && s[i])
                i++;
        return (i);
}

char     **ft_free_2(char **str, int y)
{
        int     i;

        i = 0;
        while (i < y)
        {
                free(str[i]);
                i++;
        }
        free(str);
        return (NULL);
}

char    **ft_split(char *s, char *c)
{
        int             i;
        int             y;
        int             nbr;
        char   			**str;

        y = 0;
        i = 0;
        if (!s)
            return (NULL);
        nbr = words_nbr(s, c);
        str = (char **)malloc((nbr + 1) * sizeof(char *));
        if (str == NULL)
                return (NULL);
        while (nbr-- > 0)
        {
                while (s[i] && ft_mini_strchr(s[i], c))
                        i++;
                str[y] = ft_substr(s, i, letters_nbr(&s[i], c));
                if (str[y] == NULL)
                        return (ft_free_2(str, y));
                i = i + letters_nbr(&s[i], c);
                y++;
        }
        str[y] = NULL;
        return (str);
}
