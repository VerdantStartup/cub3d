/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:36:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/09 15:44:42 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

char    *open_path(char *line)
{
    char    *path;
    int     fd;
    int     i;

    i = 0;
    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
        i++;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    path = ft_strtrim(line +i, "\n ");
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (NULL);
    close(fd);
    return (path);
}

int check_path(char *line)
{
    int path;
    int i;

    path = 0;
    i = 0;
    if (line)
    {
        while (line[i])
        {
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
                i++;
            while (line[i] && (line[i] == ' ' || line[i] == '\t'))
                i++;
            if (line[i] != '\0' && line[i] != '\n')
                path++;
        }
    }
    return (path);
}


void parse_directions(t_data *data, char *line, t_info *ptr)
{
    int     i;
    char    *path;

    i = 0;
    
    if (check_path(line) != 1)
    {
        data->info = ptr;
        printf("the line: %s\n", line);
        exit_error(data, 1, "Cub3d: Invalid identifier or path");
    }
    path = open_path(line);
    if (path == NULL)
        exit_error(data, 1, "Cub3d: No such file");
    data->info->elem = malloc(sizeof(char *) * 2);
    data->info->elem[0] = ft_strdup(path);
    data->info->elem[1] = NULL;
}

