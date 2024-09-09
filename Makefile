NAME = Philosophers
INCLUDES = -I inc
SRCS =	src/main.c \
	src/init.c \
	src/cycle.c \
	src/checker.c \
	src/utils.c \

OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) && printf "Compiling: $(notdir $<)"

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all, clean, fclean, re

.SILENT:
