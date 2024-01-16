# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 10:15:10 by aleite-b          #+#    #+#              #
#    Updated: 2024/01/15 16:54:30 by aleite-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
ARCHIVES = libft/libft.a

SOURCES = main.c \
			parsing/env_init.c \
			parsing/files.c \
			parsing/parsing.c \
			parsing/tokens.c \
			parsing/args.c \
			parsing/utils.c \
			parsing/utils2.c \
			
OBJECTS = $(SOURCES:.c=.o)

.c.o:
	$(CC) $(FLAGS) -I. -c $< -o $@

$(NAME): $(OBJECTS) 
	make all -C libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(ARCHIVES) -lreadline

all: $(NAME)

re: clean fclean all

clean:
	$(RM) $(OBJECTS)
	make fclean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft


.PHONY: all clean fclean re bonus