# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 12:19:01 by pjerddee          #+#    #+#              #
#    Updated: 2022/08/09 00:16:29 by pjerddee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRCS =	ft_pipex.c

CFLAGS = -Wall -Werror -Wextra

INC_DIR = .libft/

OBJS = $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	@gcc -c $(CFLAGS) -I $(INC_DIR) -lft $(SRCS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -f *.o

all: $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
