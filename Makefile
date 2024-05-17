NAME = Philosophers
LIBFT = inc/Libft/libft.a
INCUDES = -I inc
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


$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C inc/Libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) && printf "Compiling: $(notdir $<)"

clean :
	$(RM) $(OBJS)
	make clean -C inc/Libft

fclean : clean
	$(RM) $(NAME)
	make fclean -C inc/Libft

re : fclean all

.PHONY: all, clean, fclean, re

.SILENT:
