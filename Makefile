NAME = philo

SRCS = create_functions.c est.c functions.c main.c utils.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean:
	rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re

