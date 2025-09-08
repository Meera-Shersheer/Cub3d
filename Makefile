NAME    = cub3d
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC_PATH    = src/
OBJ_PATH    = build/
INCLUDE     = include/
LIBFT_PATH  = lib/libft/

LIBFT          = $(LIBFT_PATH)libft.a
LIBFT_FLAGS    = -L$(LIBFT_PATH) -lft
MLX42_FLAGS	   = -Imlx42/include -Lmlx42/build -lmlx42 -ldl -lglfw -pthread -lm

SRC_FILES	   = main check_av parsing init check_argument 
SRC         = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_PATH), $(addsuffix .o, $(SRC_FILES)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $(OBJ) $(LIBFT_FLAGS) $(MLX42_FLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | build
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory

build:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
