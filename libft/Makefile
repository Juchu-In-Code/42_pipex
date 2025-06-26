# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:08 by jgalizio          #+#    #+#              #
#    Updated: 2024/09/20 17:54:46 by jgalizio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
CFLAGS			= -Wall -Werror -Wextra
AR				= ar crs
RM				= rm -f
HEADER			= libft.h

SOURCES 		= \
					ft_atoi.c \
 	   				ft_bzero.c \
 	   				ft_calloc.c \
 	   				ft_isalnum.c \
 	   				ft_isalpha.c \
 	   				ft_isascii.c \
 	   				ft_isdigit.c \
 	   				ft_isprint.c \
 	   				ft_itoa.c \
 	   				ft_lstadd_back.c \
 	   				ft_lstadd_front.c \
 	   				ft_lstclear.c \
 	   				ft_lstdelone.c \
 	   				ft_lstiter.c \
 	   				ft_lstlast.c \
 	   				ft_lstmap.c \
 	   				ft_lstnew.c \
 	   				ft_lstsize.c \
 	   				ft_memchr.c \
 	   				ft_memcmp.c \
 	   				ft_memcpy.c \
 	   				ft_memmove.c \
 	   				ft_memset.c \
 	   				ft_printf.c \
 	   				ft_putchar_fd.c \
 	   				ft_putendl_fd.c \
 	   				ft_puthex_fd.c \
 	   				ft_putmemaddr_fd.c \
 	   				ft_putnbr_fd.c \
 	   				ft_putstr_fd.c \
 	   				ft_putunbr_fd.c \
 	   				ft_split.c \
 	   				ft_strchr.c \
 	   				ft_strdup.c \
 	   				ft_striteri.c \
 	   				ft_strjoin.c \
 	   				ft_strlcat.c \
 	   				ft_strlcpy.c \
 	   				ft_strlen.c \
 	   				ft_strmapi.c \
 	   				ft_strncmp.c \
 	   				ft_strnstr.c \
 	   				ft_strrchr.c \
 	   				ft_strtrim.c \
 	   				ft_substr.c \
 	   				ft_tolower.c \
 	   				ft_toupper.c \
 	   				get_next_line.c

OBJECTS			= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Creating $(NAME)..."
	@$(AR) $@ $^
	@echo "$(NAME) created successfully!"

%.o: %.c $(HEADER)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJECTS)
	@echo "Object files removed."

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
