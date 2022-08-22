# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 12:19:01 by pjerddee          #+#    #+#              #
#    Updated: 2022/08/18 04:23:49 by pjerddee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =	pipex.c\
		utils.c

CFLAGS = -Wall -Werror -Wextra

INC_DIR = ./libft/

LIBFT_DIR = ./libft/

$(NAME):
	@gcc $(CFLAGS) -I$(INC_DIR) -L$(LIBFT_DIR) $(SRCS) -lft -o $(NAME)

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
