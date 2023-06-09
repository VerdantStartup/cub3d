/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:53:24 by verdant           #+#    #+#             */
/*   Updated: 2023/06/09 15:44:24 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "parser.h"

// TODO:
// 1. Wait for the parser to be done
// 2. Refactor my code to accomodate the parser all structure
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


// https://github.com/ahammout
int	main(int argc, char **argv)
{
	t_all		all;
	
	if (argc != 2)
		return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , 1);
	parser(argv, &data)
	// if (!init_structs(&all)) // Init textures inside of init_structs
	// 	return (EXIT_FAILURE);
	// if (!all.player_drawn) // Refactor after parser is done
	// 	draw_minimap(&all);
	// cast_rays(&all, &all.ray, &all.player);
	// mlx_loop_hook(all.mlxVars.mlx, &key_hook, &all);
	// mlx_loop(all.mlxVars.mlx);
	return (0);
}


// int	main(void)
// {
// 	t_all		data;
// 	t_mlxVars *mlxVars = &data.mlxVars;

// 	if (!init_structs(&data)) // Init textures inside of init_structs
// 		return (EXIT_FAILURE);


// 	// mlx_texture_t *texture = mlx_load_png("/Users/mwilsch/Documents/myOwnGit/cub3d/appel.png");
// 	// if (!texture)
// 	// 	return (EXIT_FAILURE);
// 	// mlx_image_t *texture_img = mlx_texture_to_image(mlxVars->mlx, texture);
// 	// if (!texture_img)
// 	// 	return (EXIT_FAILURE);
// 	xpm_t *texture = mlx_load_xpm42("/Users/mwilsch/Documents/myOwnGit/cub3d/brick.xpm42");
// 	if (!texture)
// 		return (EXIT_FAILURE);
// 	mlx_image_t *texture_img = mlx_texture_to_image(mlxVars->mlx, &texture->texture);
// 	if (!texture_img)
// 		return (EXIT_FAILURE);
	


// 	data.mlxVars.texture_img = texture_img;





		
// 	if (!data.player_drawn) // Refactor after parser is done
// 		draw_minimap(&data);
// 	cast_rays(&data, &data.ray, &data.player);
// 	mlx_loop_hook(data.mlxVars.mlx, &key_hook, &data);
// 	mlx_loop(data.mlxVars.mlx);
// 	return (0);
// }
