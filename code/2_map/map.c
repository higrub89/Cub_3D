/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:26 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 15:15:03 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Controlador MAP - Recolecta Responsabilidades.
void	ft_ctrl_map(t_grl *grl)
{
	ft_validate_map_closure(grl);
	ft_validate_player_start(grl);
	ft_validate_map_characters(grl);
	ft_validate_exterior_access(grl);
	ft_normalize_map_dimensions(grl);
	ft_build_navigable_map(grl);
	ft_store_player_start(grl);
	ft_calculate_final_dimensions(grl);
}
