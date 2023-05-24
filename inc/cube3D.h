/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:31:41 by verdant           #+#    #+#             */
/*   Updated: 2023/05/24 16:01:21 by verdant          ###   ########.fr       */
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
// # include "../lib/MLX42/include/MLX42/MLX42_Input.h"
// # include "../lib/MLX42/include/MLX42/MLX42_Int.h"

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900
#define GRID_WIDTH 10
#define GRID_HEIGHT 10
#define CELL_SIZE 32
#define PADDING 0
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
	NO_MOVEMENT
} t_move;

typedef struct mlxVars_s
{
	void	*mlx;
	void	*img;
} t_mlxVars;

/**
 * @brief Structure to hold the player's position and direction
 * 
 * @param size	Size of the player in pixels
 * @param x			Starting X position of the player
 * @param y			Starting Y position of the player
 */
typedef struct player_s
{
	int	x;
	int	y;
	int	dirX;
	int	dirY;
	u_int32_t	color;
	u_int32_t	size;
	int arr[4];
} t_player;

typedef struct data_s
{
	t_mlxVars	mlxVars;
	t_player	player;
	int				map[GRID_HEIGHT][GRID_WIDTH];
	bool			map_loaded;
	uint32_t	color[2];
} t_data;




/*			Function to setup, use and clean the MLX relevant Funcs				*/
bool	init_structs(t_data *data);

/*			Functions to draw stuff				*/
void	draw_player(t_mlxVars *mlxVars, t_player *p, uint32_t color);
void	draw_2d_grid(t_data *data, t_mlxVars *mlxVars);



# endif