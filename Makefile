# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 21:26:34 by akovalyo          #+#    #+#              #
#    Updated: 2020/07/07 12:15:36 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SYSTEM := $(shell uname)
NAME=minirt
FLAGS=-Wall -Wextra -Werror -o $(NAME)
SRC_FOLDER = srcs/
LIBFT_DIR = libft/
LIBFT_INCL = libft/includes/
INCL = includes/
MAC_MACRO = -D MAC
LIN_MACRO = -D LIN
MAC_MLX_DIR = minilibx/
LIN_MLX_DIR = minilibx_lin/
MAC_FLAGS = -lmlx -framework OpenGL -framework AppKit
LIN_FLAGS = -lmlx -lm -lX11 -lXext

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

.PHONY = all clean fclean re test1 memory

ifeq ($(SYSTEM),Darwin)
	MLX_DIR = $(MAC_MLX_DIR)
	MLX_FLAGS = $(MAC_FLAGS)
	FLAGS += $(MAC_MACRO)
endif
ifeq ($(SYSTEM),Linux)
	MLX_DIR = $(LIN_MLX_DIR)
	MLX_FLAGS = $(LIN_FLAGS)
	FLAGS += $(LIN_MACRO)
endif

$(NAME): 
	@make -C $(LIBFT_DIR) re
	@make -C $(MLX_DIR) re
	@gcc $(FLAGS) $(SRCS) -I $(MLX_DIR) -L $(MLX_DIR) $(MLX_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL)

all: $(NAME)
	
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OF)

fclean: clean 
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	@rm -f $(NAME)

re: fclean all

test1:
	@gcc $(FLAGS) -g $(SRCS) -I $(MLX_DIR) -L $(MLX_DIR) $(MLX_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL)
	
memory:
	@clang $(FLAGS) -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) -I $(MLX_DIR) -L $(MLX_DIR) $(MLX_FLAGS) -I $(LIBFT_INCL) -L $(LIBFT_DIR) -lft -I $(INCL)

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCL)*.h $(LIBFT_DIR)*.c $(LIBFT_INCL)*.h
