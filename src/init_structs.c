
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
		{1, 0, 0, 0, E, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

bool	init_mlx42(t_mlxVars *mlxVars)
{
	const uint32_t color = 0xFFFFFFFF; // Blue
	mlxVars->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D", true);
	if (!mlxVars->mlx)
		return (false);
	mlxVars->img = mlx_new_image(mlxVars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlxVars->minimap_img = mlx_new_image(mlxVars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlxVars->img || !mlxVars->minimap_img)
		return (false);
	mlx_image_to_window(mlxVars->mlx, mlxVars->img, 0, 0);
	mlx_image_to_window(mlxVars->mlx, mlxVars->minimap_img, 0, 0);
	mlx_set_instance_depth(mlxVars->minimap_img->instances, 1);
	return (true);
}

// Refactor this as soon as I have the parser
void	init_player(t_data *data, int xDraw, int yDraw, int dir)
{
	const 		double 	arr_FOV[4] = {0.66, -0.66, 0.66, -0.66};
	const 		double arr[4] = {-1, 1, 1, -1};
	t_ray 		*ray;
	t_player	*player;
	
	player = &data->player;
	ray = &data->ray;
	player->size = 4;
	player->x_pixel = (CELL_SIZE / 2) - (player->size / 2) + xDraw;
	player->y_pixel = (CELL_SIZE / 2) - (player->size / 2) + yDraw;
	player->color = 0xFFFF00FF; // Yellow
	player->dir = dir;
	draw_screen_player(&data->mlxVars, player, player->color);
	player->dir_x = 0;
	player->dir_y = 0;
	if (dir == NORTH || dir == SOUTH)
		player->dir_y = arr[dir];
	if (dir == EAST || dir == WEST)
		player->dir_x = arr[dir];
	if (player->dir == NORTH || player->dir == SOUTH)
		ray->plane_x = arr_FOV[player->dir];
	if (player->dir == EAST || player->dir == WEST)
		ray->plane_y = arr_FOV[player->dir];

}

bool	init_raycaster(t_ray *ray)
{
	ray->cam_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = false;
	return (true);
}

bool init_textures(void)
{
	// Example 1 - Load from xpm42

	// 	xpm_t* xpm = mlx_load_xpm42("/Users/verdant/Documents/cub3d/brick.xpm42");
	// 	if (!xpm)
	// 		return (2);
	// 	mlx_image_t* texture = mlx_texture_to_image(mlxVars->mlx, &xpm->texture);
	// 	if (!texture)
	// 		return (3);
	// 	if (mlx_image_to_window(mlxVars->mlx, texture, 0, 0) < 0)
	// 		return (4);

	// Example 2 - Load from png

	// 	mlx_texture_t * texture = mlx_load_png("/Users/verdant/Documents/cub3d/appel.png");
	// 	mlx_image_t* img = mlx_texture_to_image(mlxVars->mlx, texture);
	// 	if (!texture)
	// 		return (3);
	// 	if (mlx_image_to_window(mlxVars->mlx, img, 0, 0) < 0)
	// 		return (4);
	
	return (true);
}

// Refactor grid variable this as soon as I have the parser from my partner
bool init_structs(t_data *data)
{
	t_mlxVars	mlxVars;
	t_ray			ray_vars;
	// t_map			map;

	if (!init_mlx42(&mlxVars) || !init_raycaster(&ray_vars))
		return (false);
	data->mlxVars = mlxVars;
	data->ray = ray_vars;
	// if (!init_textures(void))
	ft_memcpy(data->world_grid, grid, sizeof(grid));
	data->player_drawn = false;
	data->celling_color = 0x00000000;
	data->cube_color = 0xFFFF00FF;
	data->floor_color = 0xFF0000FF;
	data->move_speed = 0.1;
	data->rot_speed = 0.1;
	return (true);
}
