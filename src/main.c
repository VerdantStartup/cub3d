/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:53:24 by verdant           #+#    #+#             */
/*   Updated: 2023/05/24 16:57:49 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"


int is_wall(t_player *player, int new_x, int new_y, t_data *data)
{
		int	grid_x_min;
		int	grid_y_min;
		int	grid_x_max;
		int	grid_y_max;

 		grid_x_min = new_x / CELL_SIZE;
 		grid_y_min = new_y / CELL_SIZE;
 		grid_x_max = (new_x + player->size - 1) / CELL_SIZE;
 		grid_y_max = (new_y + player->size - 1) / CELL_SIZE;
		if (data->map[grid_y_min][grid_x_min] == 1) 
			return 1;
		if (data->map[grid_y_min][grid_x_max] == 1) 
			return 1;
		if (data->map[grid_y_max][grid_x_min] == 1) 
			return 1;
		if (data->map[grid_y_max][grid_x_max] == 1) 
			return 1;
		return 0;
}

void move_player(t_mlxVars *mlxVars, t_player *player, t_move move, t_data *data)
{
	const int step_arr[4] = {-1, 1, -1, 1};
	int new_x;
	int new_y;

	new_x = player->x;
	new_y = player->y;
	if (move == FORWARD || move == BACKWARD)
		new_y += step_arr[move];
	if (move == LEFT || move == RIGHT)
		new_x += step_arr[move];
	if(is_wall(player, new_x, new_y, data))
		return;
	draw_player(mlxVars, player, 0xFF0000FF);
	player->x = new_x;
	player->y = new_y;
	draw_player(mlxVars, player, player->color); 
}



void	key_hook(void* param)
{
	t_data		*data;
	t_mlxVars	*mlxVars;
	t_player	*player;

	data = (t_data *)param;
	if (!data)
		return ;
	mlxVars = &data->mlxVars;
	player = &data->player;
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_Q))
		return (mlx_close_window(data->mlxVars.mlx));
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_W))
		move_player(mlxVars, player, FORWARD, data);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_S))
		move_player(mlxVars, player, BACKWARD, data);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_A))
		move_player(mlxVars, player, LEFT, data);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_D))
		move_player(mlxVars, player, RIGHT, data);
}
int	main(void)
{
	t_data	data;
	if (!init_structs(&data))
		return (EXIT_FAILURE);
	if (!data.map_loaded)
		draw_2d_grid(&data, &data.mlxVars);
	mlx_loop_hook(data.mlxVars.mlx, &key_hook, &data);
	mlx_loop(data.mlxVars.mlx);
	return (0);
}