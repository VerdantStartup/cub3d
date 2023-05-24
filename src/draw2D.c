/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:16:29 by verdant           #+#    #+#             */
/*   Updated: 2023/05/24 15:12:02 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void drawBorder(t_mlxVars *mlxVars, uint32_t borderColor)
{
		const uint32_t	lastY = GRID_HEIGHT * CELL_SIZE - PADDING;
		const uint32_t	lastX = GRID_WIDTH * CELL_SIZE - PADDING;
		u_int32_t	x;
		u_int32_t	y;
		
		// Top and Bottom borders
		for (x = xOFFSET; x < GRID_WIDTH * CELL_SIZE + xOFFSET; x++)
		{
			mlx_put_pixel(mlxVars->img, x, yOFFSET, borderColor); // Top border
			mlx_put_pixel(mlxVars->img, x, lastY + yOFFSET, borderColor); // Bottom border
		}

		// Left and Right borders
		for (y = yOFFSET; y < GRID_HEIGHT * CELL_SIZE + yOFFSET; y++)
		{
			mlx_put_pixel(mlxVars->img, xOFFSET, y, borderColor); // Left border
			mlx_put_pixel(mlxVars->img, lastX + xOFFSET , y, borderColor); // Right border
		}
}

void	draw_cell(int idx, t_mlxVars *mlxVars, int xDraw, int yDraw)
{
	const uint32_t colors[2] = {0xFF0000FF, 0x000000FF};
	u_int32_t		x;
	u_int32_t		y;

	if (!mlxVars)
		return ;
	if (idx > 1)
		idx = 0;
	x = 0;
	while (x < CELL_SIZE - PADDING)
	{
		y = 0;
		while (y < CELL_SIZE - PADDING)
		{
			mlx_put_pixel(mlxVars->img, x + xDraw, y + yDraw, colors[idx]);
			y++;
		}
		x++;
	}
}

void draw_player(t_mlxVars *mlxVars, t_player *p, uint32_t color)
{
	int	x;
	int	y;
	
	x = 0;
	while (x < p->size)
	{
		y = 0;
		while (y < p->size)
		{
			mlx_put_pixel(mlxVars->img, x + p->x, y + p->y, color);
			y++;
		}
		x++;
	}
}

void	init_player(t_data *data, int xDraw, int yDraw, int direction)
{
	t_player	*player;
	
	player = &data->player;
	player->size = 4;
	player->x = CELL_SIZE / 2 - (player->size / 2);
	player->y = CELL_SIZE / 2 - (player->size / 2);
	player->x += xDraw;
	player->y += yDraw;
	player->dirX = 0;
	player->dirY = 0;
	player->color = 0xFFFF00FF; // Yellow
	player->arr[N - 2] = player->dirX = 1;
	player->arr[S - 2] = player->dirX = -1;
	player->arr[E - 2] = player->dirY = 1;
	player->arr[W - 2] = player->dirY = -1;
	if (direction == 0 || direction == 1)
		player->dirY = player->arr[direction];
	if (direction == 2 || direction == 3)
		player->dirX = player->arr[direction];
	draw_player(&data->mlxVars, player, player->color);
}


void	draw_2d_grid(t_data *data, t_mlxVars *mlxVars)
{
	int	x;
	int	y;
	int	xDraw;
	int	yDraw;

	y = 0;
	while (y < GRID_HEIGHT)
	{
		x = 0;
		while (x < GRID_WIDTH)
		{
			xDraw = x * CELL_SIZE + xOFFSET;
			yDraw = y * CELL_SIZE + yOFFSET;
			draw_cell(data->map[y][x], &data->mlxVars, xDraw, yDraw);
			if (data->map[y][x] > 1)
				init_player(data, xDraw, yDraw, data->map[y][x] - 2);
			x++;
		}
		y++;
	}
	data->map_loaded = true;
}
