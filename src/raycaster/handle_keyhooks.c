/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyhooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:27:51 by verdant           #+#    #+#             */
/*   Updated: 2023/06/09 15:43:48 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

/**
 * @brief 
 * 
 * @param player 
 * @param new_x 
 * @param new_y 
 * @param data 
 * @note I'm checking every corner of the player against the world_grid
 */
bool is_wall_in_world(t_player *player, int new_x, int new_y, t_data *data)
{
		int	grid_x_min;
		int	grid_y_min;
		int	grid_x_max;
		int	grid_y_max;

 		grid_x_min = new_x / CELL_SIZE;
 		grid_y_min = new_y / CELL_SIZE;
 		grid_x_max = (new_x + player->size - 1) / CELL_SIZE;
 		grid_y_max = (new_y + player->size - 1) / CELL_SIZE;
		if (data->world_grid[grid_y_min][grid_x_min] == 1) 
			return true;
		if (data->world_grid[grid_y_min][grid_x_max] == 1) 
			return true;
		if (data->world_grid[grid_y_max][grid_x_min] == 1) 
			return true;
		if (data->world_grid[grid_y_max][grid_x_max] == 1) 
			return true;
		return false;
}

// void move_player(t_player *player, t_move move, double move_speed)
// {
// 	// TODO: Implement wall collision
// 	int new_x;
// 	int new_y;
	
// 	if (move == FORWARD)
// 	{
// 		player->x_grid += player->dir_x * move_speed;
// 		player->y_grid += player->dir_y * move_speed;
// 	}
// 	if (move == BACKWARD)
// 	{
// 		player->x_grid -= player->dir_x * move_speed;
// 		player->y_grid -= player->dir_y * move_speed;
// 	}
// 	if (move == LEFT)
// 	{
// 		player->x_grid -= player->dir_y * move_speed;
// 		player->y_grid += player->dir_x * move_speed;
// 	}
// 	if (move == RIGHT)
// 	{
// 		player->x_grid += player->dir_y * move_speed;
// 		player->y_grid -= player->dir_x * move_speed;
// 	}
// }

void move_player(t_player *player, t_move move, double move_speed, int grid[GRID_HEIGHT][GRID_WIDTH])
{
	const		int arr[2] = {1, -1};
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (move == FORWARD || move == BACKWARD)
	{
		new_x = player->x_grid + player->dir_x * move_speed * arr[move];
		new_y = player->y_grid + player->dir_y * move_speed * arr[move];
	}
	if (move == LEFT)
	{
		new_x = player->x_grid - player->dir_y * move_speed;
		new_y = player->y_grid + player->dir_x * move_speed;
	}
	if (move == RIGHT)
	{
		new_x = player->x_grid + player->dir_y * move_speed;
		new_y = player->y_grid - player->dir_x * move_speed;
	}
	if (grid[(int)new_y][(int)new_x] == 1) 
		return ;
	player->y_grid = new_y;
	player->x_grid = new_x;
}


void	rotate_player(t_player *player, t_move move, double rot_speed,  t_data *data)
{
	if (move == ROTATE_LEFT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		player->dir_y = oldDirX * sin(rot_speed) + player->dir_y * cos(rot_speed);
		double old_plane_x = data->ray.plane_x; // Could this sefault if rays haven't be casted yet
		data->ray.plane_x = data->ray.plane_x * cos(rot_speed) - data->ray.plane_y * sin(rot_speed);
		data->ray.plane_y = old_plane_x * sin(rot_speed) + data->ray.plane_y * cos(rot_speed);
	}
	if (move == ROTATE_RIGHT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		player->dir_y = oldDirX * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		double old_plane_x = data->ray.plane_x; // Could this sefault if rays haven't be casted yet
		data->ray.plane_x = data->ray.plane_x * cos(-rot_speed) - data->ray.plane_y * sin(-rot_speed);
		data->ray.plane_y = old_plane_x * sin(-rot_speed) + data->ray.plane_y * cos(-rot_speed);
	}
}

void	key_hook(void* param)
{
	t_data		*data;
	t_mlxVars	*mlxVars;
	t_player	*player;

	data = (t_data *)param;
	mlxVars = &data->mlxVars;
	player = &data->player;
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_Q))
		return (mlx_close_window(data->mlxVars.mlx));
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_W))
		move_player(player, FORWARD, data->move_speed, data->world_grid);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_S))
		move_player(player, BACKWARD, data->move_speed,data->world_grid);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_A))
		move_player(player, LEFT, data->move_speed, data->world_grid);	
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_D))
		move_player(player, RIGHT, data->move_speed, data->world_grid);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_LEFT))
		rotate_player(player, ROTATE_LEFT,data->rot_speed, data);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_RIGHT))
		rotate_player(player, ROTATE_RIGHT,data->rot_speed, data);
	// draw_minimap(data);
	cast_rays(data, &data->ray, &data->player);
}
