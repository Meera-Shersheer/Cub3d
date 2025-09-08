# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 09:09:38 by aalmahas          #+#    #+#              #
#    Updated: 2024/09/22 09:09:43 by aalmahas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS =  ft_split.c ft_itoa.c ft_striteri.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c   ft_isprint.c  ft_memcpy.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c  \
	ft_strrchr.c ft_strnstr.c ft_tolower.c ft_toupper.c ft_bzero.c ft_memchr.c ft_memcmp.c ft_memset.c ft_memmove.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strtrim.c ft_strmapi.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_strjoin.c
# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
NAME = libft.a

# Default rule
all: $(NAME)

# Rule to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets to avoid conflicts with files named 'clean', 'fclean', 're'
.PHONY: all clean fclean re

