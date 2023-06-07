/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:16:29 by verdant           #+#    #+#             */
/*   Updated: 2023/05/29 15:29:39 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	draw_minimap_cell(int idx, t_mlxVars *mlxVars, int x_pixel, int y_pixel)
{
	const uint32_t colors[2] = {0xFF0000FF, 0x000000FF};
	u_int32_t		x;
	u_int32_t		y;

	if (!mlxVars)
		return ;
	if (idx > 1)
		idx = 0;
	x = 0;
	while (x <= CELL_SIZE)
	{
		y = 0;
		while (y <= CELL_SIZE)
		{
			if (y != CELL_SIZE - 1 && x != CELL_SIZE - 1)
				mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, colors[idx]);
			else
				mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, 0xFFFFFFF);
			y++;
		}
		x++;
	}
}

void draw_screen_player(t_mlxVars *mlxVars, t_player *p, uint32_t color)
{
	u_int32_t	x;
	u_int32_t	y;
	
	x = 0;
	while (x < p->size)
	{
		y = 0;
		while (y < p->size)
		{
			mlx_put_pixel(mlxVars->minimap_img, x + p->x_pixel, y + p->y_pixel, color);
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x_grid;
	int	y_grid;
	int	x_pixel;
	int	y_pixel;

	y_grid = 0;
	while (y_grid < GRID_HEIGHT)
	{
		x_grid = 0;
		while (x_grid < GRID_WIDTH)
		{
			x_pixel = x_grid * CELL_SIZE + xOFFSET;
			y_pixel = y_grid * CELL_SIZE + yOFFSET;
			draw_minimap_cell(data->world_grid[y_grid][x_grid], &data->mlxVars, x_pixel, y_pixel);
			if (!data->player_drawn && data->world_grid[y_grid][x_grid] > 1)
			{	
				data->player.x_grid = x_grid + 0.5;
				data->player.y_grid = y_grid + 0.5;
				init_player(data, x_pixel, y_pixel, data->world_grid[y_grid][x_grid] - 2);
			}
			x_grid++;
		}
		y_grid++;
	}
	data->player_drawn = true;
}
