# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 16:26:45 by adpinhei          #+#    #+#              #
#    Updated: 2025/12/04 13:01:34 by brmaria-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#                            Target and Compiler                              #
###############################################################################
NAME := minishell

CC := cc

###############################################################################
#                                    Flags                                    #
###############################################################################
FLAGS = -Wall -Wextra -Werror -g
LDFLAGS := -lreadline

###############################################################################
#                                    vpath                                    #
###############################################################################
vpath %.h includes
vpath %.c error
vpath %.c parsing
vpath %.c exec
vpath %.c builtins
vpath %.c signals

###############################################################################
#                            Libft path and archive                           #
###############################################################################
LIBFT_PATH := ./libft
LIBFT := $(LIBFT_PATH)/libft.a

###############################################################################
#                              Builds' Directory                              #
###############################################################################
BUILD_DIR := build

###############################################################################
#                               Source Files                                  #
###############################################################################

ERROR_FILES := clean_cmd.c clean_env.c clean_shell.c clean_tokens.c \
				clean_utils.c

PARSE_FILES := loop.c my_exit.c input_checker.c lexer.c parser_utils.c \
				parser.c shell_init.c token_maker.c syntax.c\
				expand_tk.c test.c token_utils.c 
				
BUILTIN_FILES := cd.c echo.c env.c exit.c export.c pwd.c unset.c is_builtin.c \

SIGNALS_FILES := signal.c

#EXEC_FILES := exec.c

SRC_FILES := $(ERROR_FILES) $(PARSE_FILES) $(BUILTIN_FILES) $(SIGNALS_FILES) $(EXEC_FILES)

###############################################################################
#                               Object Files                                  #
###############################################################################
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

###############################################################################
#                                 Includes                                    #
###############################################################################
INCLUDES := minishell.h parser.h


###############################################################################
#                                Debug Flags                                  #
###############################################################################
gdb: FLAGS += -g
leak: FLAGS += -fsanitize=address,undefined -g

###############################################################################
#                                Basic Rules                                  #
###############################################################################
.PHONY: all clean fclean re valgrind norm gdb

all: $(BUILD_DIR) $(LIBFT) $(NAME)

###############################################################################
#                                   Libft                                     #
###############################################################################
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)

###############################################################################
#                               Create ./build                                #
###############################################################################
$(BUILD_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Creating$(RESET) $(BUILD_DIR)"
	@echo "$(GREEN)Compiled objects$(RESET)"

###############################################################################
#                        Compile objects into /build                          #
###############################################################################
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

###############################################################################
#                               Build executable                              #
###############################################################################
$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(YELLOW)Compiled$(RESET) $(NAME)"

###############################################################################
#                                Debug Rules                                  #
###############################################################################
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

gdb: $(NAME)
	@gdb --tui ./$(NAME)

leak: $(NAME)
	@echo "$(YELLOW)Running with sanitizers (adress, leak, undefined)$(RESET)"
	@./$(NAME)

###############################################################################
#                                  Clean up                                   #
###############################################################################
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

###############################################################################
#                                    Help                                     #
###############################################################################
help:
	@echo "$(YELLOW)Available targets:$(RESET)"
	@echo "  all           - Build the mandatory executable"
	@echo "  clean         - Remove object files"
	@echo "  fclean        - Remove all built files"
	@echo "  re            - Clean and rebuild everything"
	@echo "  norm          - Run norminette checks"
	@echo "  valgrind      - Run valgrind on mandatory"
	@echo "  gdb           - Start gdb on mandatory"

###############################################################################
#                               Color Codes                                   #
###############################################################################
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m