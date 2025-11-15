# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 14:16:51 by brmaria-          #+#    #+#              #
#    Updated: 2025/11/14 14:38:49 by brmaria-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME = minishell

# compiler and flags:
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft

# Libft directory
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# basic and additional files:
SRC =	main.c\
		echo.c\
		env.c\
		export.c\
		pwd.c
	
OBJ = $(SRC:.c=.o)

RM = rm -rf

# standard rule:
all: $(NAME)

# compile and create the lib:
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lm
	@echo "Let's build this Minishell! Done!"

# compile .o:
%.o: %.c fdf.h
	@$(CC) $(CFLAGS) -Ilibft -c $< -o $@
	@echo "Compiling $<..."


$(LIBFT):
	@echo "Making Libft..."
	@make -C $(LIBFT_DIR)
	
# clean files:
clean:
	@$(RM) $(OBJ)
	@echo "Off with these files!"

# clean everything, .o and libft.a:
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "Binary gone!"

# recompile all:
re: fclean all

.PHONY: all re clean fclean

