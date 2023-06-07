/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:31:41 by verdant           #+#    #+#             */
/*   Updated: 2023/05/29 15:12:57 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900
#define GRID_WIDTH 10
#define GRID_HEIGHT 10
#define CELL_SIZE 32
#define ROT_SPEED 3.0
#define PADDING 1
#define xOFFSET 0
#define yOFFSET 0
#define N 2
#define S 3
#define E 4
#define W 5

typedef enum e_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	NO_MOVEMENT
} t_move;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_direction;

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL
} t_side;
typedef struct s_mlxVars
{
	mlx_t				*mlx;
	mlx_image_t	*img;
	mlx_image_t	*minimap_img;
} t_mlxVars;

/**
 * @brief Structure to hold the player's position and direction
 * 
 * @param size	Size of the player in pixels
 * @param x			Starting X position of the player
 * @param y			Starting Y position of the player
 * @param dir_x	x component of the player's direction vector
 * @param dir_y	y component of the player's direction vector
 * @param color	Color of the player
 * @param arr_dir	Array of directions
 */
typedef struct s_player
{
	double	x_pixel;
	double	x_grid;
	double	y_pixel;
	double	y_grid;
	double			dir_x;
	double			dir_y;
	t_direction dir;
	u_int32_t	color;
	u_int32_t	size;
} t_player;

typedef struct s_ray
{
	double		cam_x;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int				line_height;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	t_side		side;
	bool			hit;
	double		perp_wall_dist;
} t_ray;

typedef struct data_s
{
	t_mlxVars	mlxVars;
	t_player	player;
	t_ray			ray;
	// Add all of this to t_map after the parser is done
	int				world_grid[GRID_HEIGHT][GRID_WIDTH]; 
	bool			player_drawn;
	uint32_t	celling_color;
	uint32_t	cube_color;
	uint32_t	floor_color;
	double		move_speed;
	double		rot_speed;
} t_data;




/*			Function to setup, use and clean the MLX relevant Funcs				*/

bool	init_mlx42(t_mlxVars *mlxVars);
bool	init_raycaster(t_ray *ray);
void	init_player(t_data *data, int xDraw, int yDraw, int direction);
bool	init_structs(t_data *data);

/*			Functions to draw stuff				*/

void	draw_minimap_cell(int idx, t_mlxVars *mlxVars, int xDraw, int yDraw);
void	draw_screen_player(t_mlxVars *mlxVars, t_player *p, uint32_t color);
void	draw_minimap(t_data *data);

/*			Functions to handle events				*/

bool	is_wall_in_world(t_player *player, int new_x, int new_y, t_data *data);
void	key_hook(void* param);

/*			Functions to cast Rays				*/

void	draw_line(mlx_image_t* image, int x1, int y1, int x2, int y2, uint32_t color);
void	init_dda_vars(t_ray *ray, t_player *player);
void	scan_grid_lines(t_ray *ray, t_data *data);
void	cast_rays(t_data *data, t_ray *ray, t_player *player);

/*			Main				*/

# endif