NAME = ft_ls

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
LFLAGS = -lft -L./libft

FILES = main

LIBFT = libft/libft.a

OBJ_DIR = obj/

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(LIBFT):
	make -C libft/

clean :
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean
	make

.PHONY : all clean fclean re