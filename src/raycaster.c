/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:41:43 by verdant           #+#    #+#             */
/*   Updated: 2023/06/07 11:02:40 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void draw_line(mlx_image_t* image, int x1, int y1, int x2, int y2, uint32_t color)
{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int sx = x1 < x2 ? 1 : -1;
		int sy = y1 < y2 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2;
		int e2;

		while (1) {
				if (x1 < 0 || x1 > SCREEN_WIDTH || y1 < 0 || y1 > SCREEN_HEIGHT)
					break;
				mlx_put_pixel(image, x1, y1, color);
				if (x1 == x2 && y1 == y2)
						break;
				e2 = err;
				if (e2 > -dx) {
						err -= dy;
						x1 += sx;
				}
				if (e2 < dy) {
						err += dx;
						y1 += sy;
				}
		}
}

void	init_dda_vars(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_grid - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x_grid) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_grid - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y_grid) * ray->delta_dist_y;
	}
}

void	scan_grid_lines(t_ray *ray, t_data *data)
{
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = VERTICAL;
		}
		if (data->world_grid[ray->map_y][ray->map_x] == 1)
			ray->hit = true;
	}
	if(ray->side == HORIZONTAL) 
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	draw_3D_on_screen(t_ray *ray, mlx_image_t *img, t_data *data, int num_ray)
{
	const int	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	const	int	half_screen_height = SCREEN_HEIGHT / 2;
	int	celling_start;
	int	cube_start;
	int	floor_start;
	
	celling_start = 0;
	cube_start = half_screen_height - line_height / 2;
	if (cube_start < 0)
		cube_start = 0;
	floor_start = half_screen_height + line_height / 2;

	
}
// void	draw_3D_on_screen(t_ray *ray, mlx_image_t *img, t_data *data, int num_ray)
// {
// 	const int	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
// 	const	int	half_screen_height = SCREEN_HEIGHT / 2;
// 	int	celling_start;
// 	int	cube_start;
// 	int	floor_start;
	
// 	celling_start = 0;
// 	cube_start = half_screen_height - line_height / 2;
// 	if (cube_start < 0)
// 		cube_start = 0;
// 	floor_start = half_screen_height + line_height / 2;
// 	// if (floor_start >= SCREEN_HEIGHT)
// 	// 	floor_start = SCREEN_HEIGHT - 1;
// 	// while (celling_start < cube_start)
// 	// 	mlx_put_pixel(img, num_ray, celling_start++, data->celling_color);
// 	// while (cube_start < floor_start)
// 	// 	mlx_put_pixel(img, num_ray, cube_start++, data->cube_color);
// 	// while (floor_start < SCREEN_HEIGHT)
// 	// 	mlx_put_pixel(img, num_ray, floor_start++, data->floor_color);	
// }

/**
 * @brief 
 * 
 * @param data 
 * @param ray 
 * @param player 
 * @note Horizontal lines are represented by x, and vertical lines are represented by y.
 * @note The delta Distance variable is a fixed distance that a ray needs to travel from one grid line to the next.
 * @note The initial side Distance Variable is the distance between the player and the next grid line. It doesn't matter if the player is on a grid line or not.
 * @note We can then increment sideDis by deltaDis because as soon as we walked inital side Distance we then always increment from one grid line to the next
 * 
 * @note delta Dis is calculated using the Pytagorem Therom and the Thales theoreom
 */
void	cast_rays(t_data *data, t_ray *ray, t_player *player)
{
	int						num_ray;
	
	num_ray = 0;
	while (num_ray < SCREEN_WIDTH)
	{
		ray->hit = false;
		ray->cam_x = 2 * (num_ray) / (double)SCREEN_WIDTH -1;
		ray->ray_dir_x = player->dir_x + ray->plane_x * ray->cam_x;
		ray->ray_dir_y = player->dir_y + ray->plane_y * ray->cam_x;;
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);;
		ray->map_x = (int)player->x_grid;
		ray->map_y = (int)player->y_grid;
		init_dda_vars(ray, player);
		scan_grid_lines(ray, data);
		draw_line(data->mlxVars.minimap_img, player->x_grid * CELL_SIZE, player->y_grid * CELL_SIZE, (player->x_grid * CELL_SIZE) + (ray->ray_dir_x * (ray->perp_wall_dist * CELL_SIZE)), (player->y_grid * CELL_SIZE) + (ray->ray_dir_y * (CELL_SIZE * ray->perp_wall_dist)), 0x00FF00FF);
		draw_3D_on_screen(ray, data->mlxVars.img, data, num_ray);
		num_ray++;
	}
}
