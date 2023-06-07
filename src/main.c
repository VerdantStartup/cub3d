/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:53:24 by verdant           #+#    #+#             */
/*   Updated: 2023/06/07 16:27:58 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// TODO:
// 1. Wait for the parser to be done
// 2. Refactor my code to accomodate the parser data structure
// 3. Implement the texture
// 4. Implement drawing the minimap over the raycaster (DONE)

/**
 * @brief 
 * 
 * @note World (coordinates/grid) always stand for working with the 2D array
 * @note Screen (pixel/grid) always stand for working with the Sreeen
 * 
 * @note I need to implement a feature that the minimap is drawn over the 
 * ray caster. But I will do this after the parser and texture is down. Because
 * I need to refactor the draw_minimap and init_player after the parser is done.
 */
int	main(void)
{
	t_data		data;
	t_mlxVars *mlxVars = &data.mlxVars;

	mlx_texture_t *texture = mlx_load_png("/Users/mwilsch/Documents/cub3d/appel.png");
	if (!texture)
		return (EXIT_FAILURE);
	mlx_image_t *texture_img = mlx_texture_to_image(mlxVars->mlx, texture);
	if (!texture_img)
		return (EXIT_FAILURE);
	
	data.texWidth = texture_img->width;
	data.texHeight = texture_img->height;
	

	
	if (!init_structs(&data)) // Init textures inside of init_structs
		return (EXIT_FAILURE);
	if (!data.player_drawn) // Refactor after parser is done
		draw_minimap(&data);
	cast_rays(&data, &data.ray, &data.player);
	mlx_loop_hook(data.mlxVars.mlx, &key_hook, &data);
	mlx_loop(data.mlxVars.mlx);
	return (0);
}


// int	main(void)
// {
// 	t_data		data;
// 	t_mlxVars *mlxVars = &data.mlxVars;
// 	if (!init_structs(&data)) // Init textures inside of init_structs
// 		return (EXIT_FAILURE);
// 	if (!data.player_drawn) // Refactor after parser is done
// 		draw_minimap(&data);
// 	cast_rays(&data, &data.ray, &data.player);
// 	mlx_loop_hook(data.mlxVars.mlx, &key_hook, &data);
// 	mlx_loop(data.mlxVars.mlx);
// 	return (0);
// }
