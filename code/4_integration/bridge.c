/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:49:58 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/25 09:51:38 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 Configura los vectores de direccion (dir) y plano de camara (plane)
 * basandose en la orientación inicial del jugador (N, S, E, W).
 * * N (0) -> Dir (0, -1) | Plane (0.66, 0)
 * S (1) -> Dir (0, 1)  | Plane (-0.66, 0)
 * E (2) -> Dir (1, 0)  | Plane (0, 0.66)
 * W (3) -> Dir (-1, 0) | Plane (0, -0.66)
 */
static void	ft_set_orientation_vectors(t_grl *grl)
{
	static const double	dir_x[] = {0.0, 0.0, 1.0, -1.0};
	static const double	dir_y[] = {-1.0, 1.0, 0.0, 0.0};
	static const double	plane_x[] = {0.66, -0.66, 0.0, 0.0};
	static const double	plane_y[] = {0.0, 0.0, 0.66, -0.66};

	if (grl->player_dir < 0 || grl->player_dir > 3)
		return ;
	grl->player.dir_x = dir_x[grl->player_dir];
	grl->player.dir_y = dir_y[grl->player_dir];
	grl->player.plane_x = plane_x[grl->player_dir];
	grl->player.plane_y = plane_y[grl->player_dir];
}

//Función Puente (Integration Layer).
//Transfiere los datos parseados por Alex (Ints, Char*) a las estructuras
//físicas y gráficas del motor de Rubén (Doubles, Vectores).
void	ft_convert_data(t_grl *grl)
{
	grl->player.pos_x = (double)grl->player_col + 0.5;
	grl->player.pos_y = (double)grl->player_row + 0.5;
	ft_set_orientation_vectors(grl);
	printf("✅ BRIDGE: Converted Data.\n");
	printf("   -> Pos: [%f, %f]\n", grl->player.pos_x, grl->player.pos_y);
	printf("   -> Dir: [%f, %f]\n", grl->player.dir_x, grl->player.dir_y);
}
