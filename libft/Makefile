# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tom <tom@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 16:02:49 by ttaquet           #+#    #+#              #
#    Updated: 2026/03/04 11:32:07 by tom              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
OPTION = -c -I
HEADER_FILE = libft.h

SRC = ft_isalnum \
ft_isalpha \
ft_isdigit \
ft_isascii \
ft_isprint \
ft_strlen \
ft_memset \
ft_bzero \
ft_memcpy \
ft_memmove \
ft_strlcpy \
ft_strlcat \
ft_toupper \
ft_tolower \
ft_strchr \
ft_strrchr \
ft_strncmp \
ft_memchr \
ft_memcmp \
ft_strnstr \
ft_atoi \
ft_calloc \
ft_strdup \
ft_substr \
ft_strjoin \
ft_split \
ft_itoa \
ft_strtrim \
ft_strmapi \
ft_striteri \
ft_putchar_fd \
ft_putstr_fd \
ft_putendl_fd \
ft_putnbr_fd \
ft_putnbr_base_fd \
$(PRINTF)

PRINTF = ft_printf_utils ft_printf

SRCS = $(addsuffix .c,$(SRC))
OBJ = $(addsuffix .o,$(SRC))

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ) $(HEADER_FILE)


