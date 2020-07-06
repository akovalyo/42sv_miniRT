# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 21:26:34 by akovalyo          #+#    #+#              #
#    Updated: 2020/07/06 12:07:58 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minirt
FLAGS=-Wall -Wextra -Werror -o
MAC_MLX_DIR = minilibx/
LIN_MLX_DIR = minilibx_lin/
MAC_FLAGS = -lmlx -framework OpenGL -framework AppKit
LIN_FLAGS = -lmlx -lm -lX11 -lXext
SRC_FOLDER = srcs/
LIBFT_DIR = libft/
LIBFT_INCL = libft/includes/
INCL = includes/
INCLLIN = includes/incl_lin/
INCLMAC = includes/incl_mac/
SRC=main.c \
	read.c \
	parser.c \
	vectors.c \
	init.c \
	window.c \
	intersections.c \
	reflections.c \
	conversions.c \
	parse_shapes.c \
	utils.c \
	create_shapes.c \
	bmp.c \
	memory.c \
	math_vect.c \
	math.c \
	create_tools.c \
	utils_amb.c

SRCS = ${addprefix ${SRC_FOLDER}, ${SRC}}

OF = $(SRC:%.c=%.o)

.PHONY = all clean fclean re libft linux

all: $(NAME)

libftcomp:
	@make -C $(LIBFT_DIR) re

mlxlin_comp:	
	@make -C $(LIN_MLX_DIR) re

mlx_comp:	
	@make -C $(MAC_MLX_DIR) re

$(NAME): mlx_comp libftcomp 
	@gcc $(FLAGS) $(NAME) $(FLAGS) $(SRCS) -I $(MAC_MLX_DIR) -L $(MAC_MLX_DIR) $(MAC_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL) -I $(INCLMAC)
	
linux: mlxlin_comp libftcomp 
	@gcc $(FLAGS) $(NAME) $(SRCS) -I $(LIN_MLX_DIR) -L $(LIN_MLX_DIR) $(LIN_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL) -I $(INCLLIN)

clean:
	@make -C $(LIBFT_DIR) clean

fclean: clean 
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

test_lin:
	@gcc $(FLAGS) $(NAME) -g $(SRCS) -I $(LIN_MLX_DIR) -L $(LIN_MLX_DIR) $(LIN_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL) -I $(INCLLIN)

test:
	@gcc $(FLAGS) $(NAME) $(FLAGS) -g $(SRCS) -I $(MAC_MLX_DIR) -L $(MAC_MLX_DIR) $(MAC_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL) -I $(INCLMAC)
	
memory_lin: 
	@clang $(FLAGS) $(NAME) -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) -I $(LIN_MLX_DIR) -L $(LIN_MLX_DIR) $(LIN_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL) -I $(INCLLIN)

memory:
	@clang $(FLAGS) $(NAME) -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) $(MAC_MLX_DIR) -L $(MAC_MLX_DIR) $(MAC_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL) -I $(INCLMAC)

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCL)*.h $(INCLLIN)*.h $(INCLMAC)*.h $(LIBFT_DIR)*.c $(LIBFT_INCL)*.h
