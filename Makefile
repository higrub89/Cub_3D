# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhiguita <rhiguita@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 12:38:40 by rhiguita          #+#    #+#              #
#    Updated: 2025/11/24 12:38:43 by rhiguita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3 -g3 # -O3 para máximo rendimiento
RM          = rm -f

# --- RUTAS ---
SRC_DIR     = code
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

# --- FUENTES (Automáticas por carpeta para máxima limpieza) ---
# 1. Parse
SRC_PARSE   = $(addprefix 1_parse/, parse.c A1_map_array.c A2_map_array_utils.c \
              B1_headers.c B2_find_map_end_index.c C1_normalize_assets.c D1_prepare_map_block.c)

# 2. Map
SRC_MAP     = $(addprefix 2_map/, map.c A1_validate_map_closure.c A2_inter_spaces.c \
              B1_validate_player_start.c C1_validate_map_characters.c D1_validate_exterior_access.c \
              D2_Flood.c E1_normalize_map_dimensions.c F1_build_navigable_map.c \
              G1_store_player_start.c H1_calculate_final_dimensions.c)

# 3. Engine (TU PARTE)
SRC_ENGINE  = $(addprefix 3_engine/, engine_init.c engine_hooks.c engine_render.c \
              engine_raycast.c engine_movement.c)

# 4. Integration
SRC_INTEG   = $(addprefix 4_integration/, bridge.c)

# CleanUp
SRC_CLEAN   = $(addprefix cleanUp/, cleanUp.c)

# Main
SRC_MAIN    = main.c

# Unimos todo
SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_MAIN) $(SRC_PARSE) $(SRC_MAP) $(SRC_ENGINE) $(SRC_INTEG) $(SRC_CLEAN))
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- LIBRERÍAS ---
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
LIBS        = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# --- REGLAS ---
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "--- CREATION ./$(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✅  SUCCESSFUL COMPILATION  ✅"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR) -c $< -o $@
	@echo "🔧 Compiling: $<"

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@make -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@make -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@echo "--- DELETION OF OBJECT FILES ---"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "--- DELETE FILE ./Cub3D ---"

re: fclean all

.PHONY: all clean fclean re
