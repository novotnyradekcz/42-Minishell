# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 10:49:44 by lmaresov          #+#    #+#              #
#    Updated: 2024/09/28 12:28:56 by rnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror # -I/opt/homebrew/Cellar/readline/8.2.13/include
LDFLAGS = -lreadline # -L/opt/homebrew/Cellar/readline/8.2.13/lib
SRCS = minishell.c\
	divide_input.c\
	env_to_listd.c\
	expand_envar_help.c\
	expand_envar.c\
	ft_libft.c\
	separate_tokens_ft_helper.c\
	separate_tokens_ft.c\
	utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o$(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
		