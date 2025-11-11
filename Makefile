# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 20:09:29 by adpinhei          #+#    #+#              #
#    Updated: 2025/11/11 18:35:50 by adpinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

FLAGS := -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS := -lreadline

vpath %.c src error parsing
vpath %.h includes

LIBFT_PATH := ./libft
LIBFT := $(LIBFT_PATH)/libft.a

BUILD_DIR := build

#Source Files
SRC_FILES := loop.c clean_tokens.c input_checker.c token_maker.c \
			token_list_maker.c cmd_list_maker.c clean_cmd_lst.c \
			clean_env.c lexer.c

#Object Files
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

#Includes
INCLUDES := minishell.h parser.h

.PHONY: all clean fclean re valgrind norm gdb

all: $(BUILD_DIR) $(LIBFT) $(NAME)

bonus: $(BUILD_DIR) $(LIBFT) $(BONUS_NAME)

#Compile library LIBFT
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)

#Create BUILD directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Creating$(RESET) $(BUILD_DIR)"
	@echo "$(GREEN)Compiled objects$(RESET)"

#Compile object files into build
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

#Building executable
$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(YELLOW)Compiled$(RESET) $(NAME)"

#Building bonus executable
$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(YELLOW)Compiled bonus executable$(RESET) $(BONUS_NAME)"

norm:
	@norminette -R CheckForbiddenSourceHeader

valgrind: $(NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full \
	--suppressions=./.supp/readline.supp \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	./$(NAME)

bonusvalgrind: $(BONUS_NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	./$(BONUS_NAME)

gdb: $(NAME)
	@gdb --tui ./$(NAME)

bonusgdb: $(BONUS_NAME)
	@gdb --tui ./$(BONUS_NAME)

#Cleanup
clean:
	@rm -rf $(BUILD_DIR)
	@make --no-print-directory -C $(LIBFT_PATH) clean
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf test_log
	@echo "$(BLUE)Cleaned test_log$(RESET)"
	@rm -rf test_bonus_log
	@echo "$(BLUE)Cleaned test_bonus_log$(RESET)"
	@rm -f $(BONUS_NAME)
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	@echo "$(BLUE)Cleaned executables$(RESET) $(NAME) $(BONUS_NAME)"

re: fclean all

#Help
help:
	@echo "$(YELLOW)Available targets:$(RESET)"
	@echo "  all           - Build the mandatory executable"
	@echo "  bonus         - Build the bonus executable"
	@echo "  clean         - Remove object files"
	@echo "  fclean        - Remove all built files"
	@echo "  re            - Clean and rebuild everything"
	@echo "  norm          - Run norminette checks"
	@echo "  valgrind      - Run valgrind on mandatory"
	@echo "  bonusvalgrind - Run valgrind on bonus"
	@echo "  gdb           - Start gdb on mandatory"
#	@echo "  bonusgdb      - Start gdb on bonus"

#Color editing
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m