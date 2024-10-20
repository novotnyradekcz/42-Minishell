# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 10:49:44 by lmaresov          #+#    #+#              #
#    Updated: 2024/10/20 08:37:35 by rnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/Cellar/readline/8.2.13/include
LDFLAGS = -lreadline -L/opt/homebrew/Cellar/readline/8.2.13/lib
SRCS = src/minishell.c \
	src/signals.c \
	src/init.c \
	src/check/check_tokens_0.c \
	src/check/check_tokens_1.c \
	src/commands/ft_cd.c \
	src/commands/ft_echo.c \
	src/commands/ft_env.c \
	src/commands/ft_exit.c \
	src/commands/ft_export.c \
	src/commands/ft_pwd.c \
	src/commands/ft_unset.c \
	src/exec/execute_0.c \
	src/exec/execute_1.c \
	src/exec/execute_2.c \
	src/exec/execute_3.c \
	src/exec/execute_4.c \
	src/exec/execute_5.c \
	src/expand/expand_0.c \
	src/expand/expand_1.c \
	src/expand/expand_2.c \
	src/lex/lexer_0.c \
	src/lex/lexer_1.c \
	src/lex/lexer_2.c \
	src/parse/parser_0.c \
	src/parse/parser_1.c \
	src/parse/parser_2.c \
	src/utils/array_insert.c \
	src/utils/envvar.c \
	src/utils/free_0.c \
	src/utils/free_1.c \
	src/utils/misc.c \
	src/libft/ft_atoi.c \
	src/libft/ft_bzero.c \
	src/libft/ft_calloc.c \
	src/libft/ft_isalnum.c \
	src/libft/ft_isalpha.c \
	src/libft/ft_itoa.c \
	src/libft/ft_lstadd_back.c \
	src/libft/ft_lstclear.c \
	src/libft/ft_lstdelone.c \
	src/libft/ft_lstnew.c \
	src/libft/ft_lstsize.c \
	src/libft/ft_split.c \
	src/libft/ft_strchr.c \
	src/libft/ft_strdup.c \
	src/libft/ft_strjoin.c \
	src/libft/ft_strlcpy.c \
	src/libft/ft_strlen.c \
	src/libft/ft_strncmp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
		