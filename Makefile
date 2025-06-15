NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCDIR = .
SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/init.c \
       $(SRCDIR)/utils.c \
       $(SRCDIR)/actions.c \
       $(SRCDIR)/simulation.c \
       $(SRCDIR)/cleanup.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
