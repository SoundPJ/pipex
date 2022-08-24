# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 12:19:01 by pjerddee          #+#    #+#              #
#    Updated: 2022/08/25 00:21:03 by pjerddee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =	pipex.c \
		utils.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c

INCS =	pipex.h \
		./gnl/get_next_line.h \
		./libft/libft.h

CFLAGS = -Wall -Werror -Wextra

INC_DIR =	libft

LIBFT_DIR = libft

GNL_DIR = gnl

BUILD_DIR = build

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(OBJS): $(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	gcc -g $(CFLAGS) -I$(GNL_DIR) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME):$(OBJS)
	make re -C $(LIBFT_DIR)	
	gcc $(CFLAGS) -I$(INC_DIR) -I$(GNL_DIR) -L$(LIBFT_DIR) $(OBJS) -lft -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS)
	norminette -R CheckDefine $(INCS)

.PHONY: all clean fclean re norm
