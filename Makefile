NAME = philo

CC = cc
CFLAGS =  -Wextra -Werror 

SRC = main.c parser.c init_philo.c utils.c init.c time.c writing.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re