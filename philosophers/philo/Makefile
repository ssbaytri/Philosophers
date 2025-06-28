NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=address

SRC  =	philo.c utils.c parse_args.c init.c monitor.c threads.c actions.c
OBJ  = $(SRC:.c=.o)
 
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re