# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 21:26:34 by akovalyo          #+#    #+#              #
#    Updated: 2020/05/18 16:45:09 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a
FLAGS=-Wall -Wextra -Werror -c
SRC=main.c \
	read.c \
	parser.c

OF = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	@make -C libft/ re
	@gcc $(FLAGS) -I ./libft/includes -c $(SRC)
	@ar rc $(NAME) $(OF) libft/*.o
	@ranlib $(NAME)

clean:
	@make -C libft/ clean
	@rm -f $(OF)

fclean: clean 
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

test:
	@gcc $(SRC) -g -I minilibx -L minilibx -lmlx -lm -lX11 -lXext -I libft/includes -L libft -lft -I includes


	
memory:
	@gcc -g -o test main.c $(SRC) -L ./libft -lft -I ./libft/includes
	@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test
	@rm test

debug:
	@gcc -g -o test main.c $(SRC) -L ./libft -lft -I ./libft/includes

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC) printf.h libft/*.c libft/includes/libft.h
