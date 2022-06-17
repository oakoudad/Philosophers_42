NAME = philo
CC = gcc
RM = rm -f
CFLAGS=	-Wall -Wextra -Werror

HEADER= philosopher.h

SRCM = ./main.c\
		./utils/list.c\
		./utils/valid_args.c\
		./utils/valid_time.c


$(NAME) : $(CLIE) $(SRV) $(HEADER)
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

clean:
	$(RM) philo
fclean: clean	

re : fclean all

.PHONY: fclean clean all
