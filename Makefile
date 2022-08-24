# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 12:19:01 by pjerddee          #+#    #+#              #
#    Updated: 2022/08/24 22:35:23 by pjerddee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =	pipex.c\
		utils.c\
		./gnl/get_next_line.c\
		./gnl/get_next_line_utils.c

INCS =	pipex.h\
		./gnl/get_next_line.h\
		./libft/libft.h\

CFLAGS = -Wall -Werror -Wextra

INC_DIR =	./libft/

LIBFT_DIR = ./libft/

GNL_DIR = ./gnl/

$(NAME):
	@gcc $(CFLAGS) -I$(INC_DIR) -I$(GNL_DIR) -L$(LIBFT_DIR) $(SRCS) -lft -o $(NAME)

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS)
	@norminette -R CheckDefine $(INCS)

.PHONY: all clean fclean re
