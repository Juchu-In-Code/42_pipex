# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:08 by jgalizio          #+#    #+#              #
#    Updated: 2024/11/11 19:52:11 by jgalizio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
RM				= rm -rf
CFLAGS			= -Wall -Werror -Wextra -I ./libft

BASE_DIR		= ./srcs-mandatory
BONUS_DIR		= ./srcs-bonus
LIBFT_DIR		= ./libft
BUILD_DIR		= ./.build
BUILD_BONUS_DIR	= $(BUILD_DIR)/bonus
BUILD_BASE_DIR	= $(BUILD_DIR)/mandatory

BASE_TARGET		= $(BUILD_BASE_DIR)/.mandatory
BONUS_TARGET	= $(BUILD_BONUS_DIR)/.bonus
LIBFT			= $(LIBFT_DIR)/libft.a
BASE_HEADERS	= $(BASE_DIR)/pipex.h
BONUS_HEADERS	= $(BONUS_DIR)/pipex_bonus.h
LIBFT_HEADERS	= $(LIBFT_DIR)/libft.h

BASE_SRCS		= $(addprefix $(BASE_DIR)/,\
					args_utils.c \
					error_utils.c \
					exec_utils.c \
					general_utils.c \
					open_utils.c \
					path_utils.c \
					pipex.c)

BONUS_SRCS		= $(addprefix $(BONUS_DIR)/,\
					args_utils_bonus.c \
					error_utils_bonus.c \
					exec_utils_bonus.c \
					general_utils_bonus.c \
					open_utils_bonus.c \
					path_utils_bonus.c \
					pipex_bonus.c)

BASE_OBJS		= $(BASE_SRCS:$(BASE_DIR)/%.c=$(BUILD_BASE_DIR)/%.o)
BONUS_OBJS		= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BUILD_BONUS_DIR)/%.o)

all: $(NAME)

$(NAME): $(BASE_TARGET)

bonus: $(BONUS_TARGET)

$(BASE_TARGET): $(BASE_OBJS) $(LIBFT)
	@echo "Creating pipex..."
	@$(CC) $(CFLAGS) $(BASE_OBJS) $(LIBFT) -o $(NAME)
	@touch $(BASE_TARGET)
	@rm -f $(BONUS_TARGET)
	@echo "Done! :D"

$(BONUS_TARGET): $(BONUS_OBJS) $(LIBFT)
	@echo "Creating bonus..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	@touch $(BONUS_TARGET)
	@rm -f $(BASE_TARGET)
	@echo "Done! :D"

$(BUILD_BASE_DIR)/%.o: $(BASE_DIR)/%.c $(BASE_HEADERS) $(LIBFT)
	@echo "compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c $(BONUS_HEADERS) $(LIBFT)
	@echo "compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_HEADERS)
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "Done! :D"

clean:
	@echo "Cleaning objects..."
	@$(RM) $(BASE_OBJS) $(BONUS_OBJS) $(BASE_TARGET) $(BONUS_TARGET)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "Done! :D"

fclean: clean
	@echo "Cleaning all..."
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "Done! :D"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean bonus fclean re rebonus
