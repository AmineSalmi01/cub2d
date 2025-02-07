/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:16:11 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/20 22:04:33 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/cub3d_bonus.h"

# ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#endif

# ifndef BUFFER_SIZE
#define BUFFER_SIZE 100000
#endif

typedef struct s_list
{
    char *str_data;
    struct s_list *next;
} t_list;

t_list  *found_last_node(t_list *list);
char    *get_next_line(int fd);
char    *get_line(t_list *list);

int     found_newline(t_list *list);
int     get_len_line(t_list *list);

void    copy_string(t_list *list, char *string);
void    free_list(t_list **list, t_list *new_node, char *buf);
void    edit_list(t_list **list);
void    append(t_list **list, char *buf);
void    creat_list(t_list **list, int fd);


