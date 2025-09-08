GREEN = \033[3;32m
YELLOW = \033[3;33m
MAGENTA = \033[3;35m
CYAN = \033[3;36m
NC = \033[0m

SRC= main.c check_arg.c 
BNS= 

NAME = cub3D
CC= cc
CFLAGS= -Wall -Wextra -Werror
#-g3 -fsanitize=address -g
BNS_NAME = cub3D
#PATH LIB
LFTDIR= ./Libft

## create an object dir 
OBJ_DIR := obj

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_BNS = $(addprefix $(OBJ_DIR)/, $(BNS:.c=.o))

all: $(NAME)
	@echo "$(GREEN)Build complete.$(NC)"

$(NAME): $(OBJ_SRC) | libft
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME) -L$(LFTDIR) -lft  -Lminilibx-linux -lmlx -lXext -lX11 -Iminilibx-linux
	@echo "$(MAGENTA)Building $(NAME)...$(NC)"

$(OBJ_DIR)/%.o: %.c
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
	$(CC) $(CFLAGS) $(OBJ_BNS) -o $(BNS_NAME) -L$(LFTDIR) -lft  -Lminilibx-linux -lmlx -lXext -lX11 -Iminilibx-linux
	@echo "$(MAGENTA)Building bonus...$(NC)"

fclean: clean
	@rm -f $(OBJ_SRC) 
	@$(MAKE) -C $(LFTDIR) fclean 
	@rm -rf $(NAME)
	@echo "$(CYAN)fClean is done.$(NC)"

re: fclean all

.PHONY: all clean fclean re libft bonus      	
