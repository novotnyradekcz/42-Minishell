# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 10:49:44 by lmaresov          #+#    #+#              #
#    Updated: 2024/10/20 17:40:13 by rnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/Cellar/readline/8.2.13/include
LDFLAGS = -lreadline -L/opt/homebrew/Cellar/readline/8.2.13/lib
SRCS = minishell.c\
	ma_helper.c\
	divide_input.c\
	divide_input_helper.c\
	env_to_listd.c\
	env_to_list_helper.c\
	env_to_listd_helper.c\
	execute_other.c\
	expand_envar_help.c\
	expand_envar.c\
	free_memory_helper.c\
	free_memory.c\
	free_memory_help.c\
	handle_redir_helper.c\
	handle_redirection.c\
	one_command.c\
	run_commands.c\
	run_pipe.c\
	separate_tokens_ft_helper.c\
	separate_tokens_ft.c\
	syntax_error.c\
	utils.c\
	commands/ft_cd.c\
	commands/ft_cd_helper.c\
	commands/ft_echo.c\
	commands/ft_env.c\
	commands/ft_exit.c\
	commands/ft_export.c\
	commands/ft_pwd.c\
	commands/ft_unset.c \
	commands/buildin_helper.c\
	utils/ft_atoi.c \
	utils/ft_split.c \
	utils/ft_strlcpy.c \
	utils/ft_is.c \
	utils/ft_memset.c \
	utils/ft_strchr.c \
	utils/ft_strcmp.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/ft_strlen.c \
	utils/ft_substr.c \


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
		