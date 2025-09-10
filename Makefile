GREEN = \033[3;32m
YELLOW = \033[3;33m
MAGENTA = \033[3;35m
CYAN = \033[3;36m
NC = \033[0m

SRC= check_arg.c  check_color.c  check_map.c  check_texture.c  cleanup.c   \
		init.c  main.c  parsing.c  print.c  read_file.c   utils.c parsing2.c validate_map.c
BNS=  

NAME= cub3D
BNS_NAME = cub3D

SRC_DIR := src
OBJ_DIR := obj
LFTDIR= ./Libft

SRC_PATH = $(addprefix $(SRC_DIR)/, $(SRC))
BNS_PATH = $(addprefix $(SRC_DIR)/, $(BNS))

CC= cc
CFLAGS= -Wall -Wextra -Werror -Iinclude -g
#-g3 -fsanitize=address -g
LIBFT  = -L$(LFTDIR) -lft
MLX42  = -L./MLX42/build/ -lmlx42 -I./MLX42/include -lglfw -ldl -lglfw -pthread -lm



OBJ_SRC = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_PATH))
OBJ_BNS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BNS_PATH))

all: $(NAME)
	@echo "$(GREEN)Build complete.$(NC)"

$(NAME): $(OBJ_SRC) | libft
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME)  $(LIBFT) $(MLX42)
	@echo "$(MAGENTA)Building $(NAME)...$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) 
	$(CC) $(CFLAGS) -c $< -o $@

libft: 
	@echo "$(MAGENTA)Building libft...$(NC)"
	@$(MAKE) -sC $(LFTDIR) bonus

clean:
	@rm -rf $(OBJ_SRC) $(OBJ_DIR)
	@$(MAKE) -sC $(LFTDIR) clean
	@echo "$(CYAN)Clean is done.$(NC)"

bonus: $(OBJ_BNS)| libft 
	$(CC) $(CFLAGS) $(OBJ_BNS) -o $(BNS_NAME) $(LIBFT) $(MLX42)
	@echo "$(MAGENTA)Building bonus...$(NC)"

fclean: clean
	@rm -f $(OBJ_SRC) 
	@$(MAKE) -C $(LFTDIR) fclean 
	@rm -rf $(NAME)
	@echo "$(CYAN)fClean is done.$(NC)"

re: fclean all

.PHONY: all clean fclean re libft bonus      	