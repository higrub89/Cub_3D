/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:32:53 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/24 12:33:36 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//Inicializa la memoria y establece valores seguros por defecto.
static void	ft_init_context(t_grl *grl)
{
	ft_bzero(grl, sizeof(t_grl));
}

//Divide la ejecución en fases lógicas claras: Parsing -> Lógica -> Motor.
static void	ft_run_pipeline(t_grl *grl, const char *map_path)
{
	printf("🔹 [1/3] SYSTEM: Parsing map data...\n");
	ft_ctrl_parse(grl, map_path);
	ft_ctrl_map(grl);
	printf("✅ [OK]  Map validated.\n");
	printf("🔹 [2/3] SYSTEM: Bridging data structures...\n");
	ft_convert_data(grl);
	printf("✅ [OK]  Data bridged.\n");
	printf("🔹 [3/3] ENGINE: Initializing graphical context...\n");
	ft_init_motor(grl);
	ft_setup_hooks(grl);
	printf("🏁 [GO]  System Ready. Entering Game Loop.\n");
	mlx_loop(grl->engine.mlx);
}

// Validacion de argumentos y lanza la orquestación.
int	main(int argc, char **argv)
{
	t_grl	grl;

	if (argc != 2)
	{
		ft_print_error("Usage: ./cub3D <path/to/map.cub>");
		return (EXIT_FAILURE);
	}
	ft_init_context(&grl);
	ft_run_pipeline(&grl, argv[1]);
	return (EXIT_SUCCESS);
}
