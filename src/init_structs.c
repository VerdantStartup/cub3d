
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:52:47 by verdant           #+#    #+#             */
/*   Updated: 2023/05/22 10:54:03 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int grid[GRID_HEIGHT][GRID_WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, N, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

bool	init_mlx42(t_mlxVars *mlxVars)
{
	int	x;
	int	y;
	
	const uint32_t color = 0xFFFFFFFF; // Blue
	mlxVars->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D", true);
	if (!mlxVars->mlx)
		return (false);
	mlxVars->img = mlx_new_image(mlxVars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlxVars->img)
		return (false);
	x = 0;
	y = 0;
	while (x < SCREEN_WIDTH)
	{
		while (y < SCREEN_HEIGHT)
			mlx_put_pixel(mlxVars->img, x, y++, color);
		y = 0;
		x++;
	}
	mlx_image_to_window(mlxVars->mlx, mlxVars->img, 0, 0);
	return (true);
}

bool init_structs(t_data *data)
{
	t_mlxVars	mlxVars;

	if (!init_mlx42(&mlxVars))
		return (false);
	data->mlxVars = mlxVars;
	// Refactor this as soon as I have the parser from my partner
	ft_memcpy(data->map, grid, sizeof(grid));
	data->map_loaded = false;
	return (true);
}
