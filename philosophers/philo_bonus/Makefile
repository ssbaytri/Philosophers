NAME = philo_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread # -g -fsanitize=address

SRC  = philo_bonus.c parsing_args_bonus.c utils_bonus.c
OBJ  = $(SRC:.c=.o)
 
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re