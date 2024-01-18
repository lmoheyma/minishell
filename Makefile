CC = cc

FLAGS = -Wall -Wextra -Werror -g

INCLUDE = -I minishell.h 

LIB = -L libft/ -lft -lreadline

SRCS = src/main.c \
		src/utils.c \
		src/exec/exec.c \
		src/exec/builtin.c \
		src/exec/here_doc.c \
		src/exec/pipe.c \
		src/builtin/cd.c \
		src/builtin/echo.c \
		src/builtin/env.c \
		src/builtin/exit.c \
		src/builtin/export.c \
		src/builtin/pwd.c \
		src/builtin/unset.c \
		src/parsing/args.c \
		src/parsing/error.c \
		src/parsing/files.c \
		src/parsing/parsing.c \
		src/parsing/tokens.c \
		src/parsing/utils.c \
		src/parsing/utils2.c \
		src/parsing/utils3.c

OBJS_BASE = $(SRCS:.c=.o)

OBJS = $(addprefix obj/,$(OBJS_BASE))

NAME = minishell

all: $(NAME)

obj :
	mkdir -p obj
	mkdir -p obj/src
	mkdir -p obj/src/builtin
	mkdir -p obj/src/exec

$(NAME) : $(OBJS)
	@echo "\n"
	make -C libft/
	@echo "\033[0;32mCompiling minishell..."
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE) $(LIB)
#	mv $(OBJS) $(OBJ_DIR)/
	@echo "\n\033[0mDone !"

obj/%.o : %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "\033[0;31m"
#	@make clean -C libft/
	@echo "\nRemoving binaries..."
	rm -f $(OBJS)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31m\nDeleting executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean $(NAME)

.PHONY: all clean fclean re
