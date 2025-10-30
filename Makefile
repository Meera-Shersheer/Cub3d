GREEN = \033[3;32m
YELLOW = \033[3;33m
MAGENTA = \033[3;35m
CYAN = \033[3;36m
NC = \033[0m


NAME= cub3D
BNS_NAME = cub3D

SRC_PARSING = check_arg.c  check_color.c  check_map.c  check_texture.c parsing.c  \
		print.c  read_file.c parsing2.c validate_map.c split.c padding.c flood_fill.c 
		
SRC_RAYCASTING = minimap.c rays.c move.c try_move.c scene_3d.c door_key.c door_key2.c symbol.c \
init_images1.c init_images2.c animation.c adjust_window_size.c 

SRC_MAIN = cleanup.c  init.c  main.c  utils.c

BNS=  


SRC_DIR := src
OBJ_DIR := obj
LFTDIR= ./Libft
PARSING_DIR := Parsing
RAYCASTING_DIR := Raycasting



SRC = $(SRC_MAIN)\
	  $(addprefix $(PARSING_DIR)/, $(SRC_PARSING)) \
	  $(addprefix $(RAYCASTING_DIR)/, $(SRC_RAYCASTING))

SRC_PATH = $(addprefix $(SRC_DIR)/, $(SRC))
BNS_PATH = $(addprefix $(SRC_DIR)/, $(BNS))

CC= cc
CFLAGS= -Wall -Wextra -Werror -Iinclude -g -fsanitize=address 
#-g3 -fsanitize=address -g
LIBFT  = -L$(LFTDIR) -lft
MLX42  = -L./MLX42/build/ -lmlx42 -I./MLX42/include -lglfw -ldl -lglfw -pthread -lm

OBJ_SRC = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_PATH))
OBJ_BNS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BNS_PATH))

all: $(NAME)

$(NAME): $(OBJ_SRC) $(LFTDIR)/libft.a
	@echo "$(MAGENTA)Building $(NAME)...$(NC)"
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME)  $(LIBFT) $(MLX42)
	@echo "$(GREEN)Build complete.$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p  $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LFTDIR)/libft.a:
	@echo "$(MAGENTA)Building libft...$(NC)"
	@$(MAKE) -sC $(LFTDIR) bonus
	@echo "$(GREEN)Building Libft is complete.$(NC)"
	
clean:
	@rm -rf $(OBJ_SRC) $(OBJ_DIR)
	@$(MAKE) -sC $(LFTDIR) clean
	@echo "$(CYAN)Clean is done.$(NC)"

bonus: $(OBJ_BNS)| libft 
	@echo "$(MAGENTA)Building bonus...$(NC)"
	$(CC) $(CFLAGS) $(OBJ_BNS) -o $(BNS_NAME) $(LIBFT) $(MLX42)

fclean: clean
	@rm -f $(OBJ_SRC) 
	@$(MAKE) -C $(LFTDIR) fclean 
	@rm -rf $(NAME)
	@echo "$(CYAN)fClean is done.$(NC)"

re: fclean all

.PHONY: all clean fclean re bonus      	