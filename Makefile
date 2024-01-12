CC = cc

FLAGS = -Wall -Wextra -Werror -g

INCLUDE = -I minishell.h 

SRCS = src/main.c \
		src/exec.c \
		src/builtin.c \
		src/here_doc.c \
		src/pipe.c \
		src/utils.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	make -C libft/
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE) -L libft/ -lft -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
