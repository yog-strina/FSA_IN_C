NAME	= fsa

SRCS	= main.c

CFLAGS	+= -W -Wall -Wextra -ansi -pedantic

OBJS	= $(SRCS:.c=.o)

CC	= gcc

$(NAME): all

all: $(OBJS) $(HEADER)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f *~

fclean: clean
	@rm -f $(NAME)

re: fclean all
