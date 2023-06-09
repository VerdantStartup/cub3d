/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:49:26 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/09 15:44:42 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int find_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

void    add_node(t_data *data, int *index_ptr, t_info **ptr)
{
    t_info  *node;

    if (*index_ptr == 0)
    {
        data->map = NULL;
        data->info = malloc(sizeof(t_info));
        if (!data->info)
            exit_error(data, 0, "Cub3d: Allocation failed");
        data->info->index = *index_ptr;
        data->info->elem = NULL;
        data->info->type = NULL;
        data->info->next = NULL;
        data->info->prev = NULL;
        *ptr = data->info;
    }
    else if (*index_ptr > 0)
    {
        node = malloc(sizeof(t_info));

        node->index = *index_ptr;
        node->elem = NULL;
        node->next = NULL;
        node->type = NULL;
        data->info->prev = data->info;
        data->info->next = node;
        data->info = data->info->next;
    }
}


void    free_array(t_data *data)
{
    int i;

    i = 0;
    if (data->info->elem)
    {
        while (data->info->elem[i])
        {
            free(data->info->elem[i]);
            i++;
        }
        free(data->info->elem);
    }
}

void    free_map(t_data *data)
{
    int i;

    i = 0;
    if (data->map)
    {
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
}

void    free_data(t_data *data)
{
    free_elements_lst(data);
    free_map(data);
}

void    free_elements_lst(t_data *data)
{
    t_info   *tofree;

    if (data->info)
    {
        while (data->info)
        {
            tofree = data->info;
            free_array(data);
            data->info = data->info->next;
            free(tofree);
        }
    }
}
void exit_error(t_data *data, int fr, char *err)
{
    if (err)
        ft_putstr_fd(err, 2);
    if (fr)
        free_data(data);
     exit (EXIT_FAILURE);
}
