NAME = pipex.a

SRCS =	pipex.c

CFLAGS = -Wall -Werror -Wextra

INC_DIR = 	.libft/\
			./gnl/

$(NAME):
	@gcc $(CFLAGS) -I $(INC_DIR) -lft $(SRCS)

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
