NAME = philo
CC = gcc
RM = rm -f
CFLAGS=	-Wall -Wextra -Werror

HEADER= philosopher.h

SRCM = ./main.c\
		./exec.c\
		./list.c\
		./utils.c\
		./parsing/valid_args.c\
		./parsing/valid_time.c

$(NAME) : $(SRCM) $(HEADER)
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

clean:
	$(RM) philo
fclean: clean	

re : fclean all

.PHONY: fclean clean all
