# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 10:49:44 by lmaresov          #+#    #+#              #
#    Updated: 2024/10/22 21:13:40 by rnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/Cellar/readline/8.2.13/include
LDFLAGS = -lreadline -L/opt/homebrew/Cellar/readline/8.2.13/lib
SRCS = src/minishell.c \
	src/ma_helper.c \
	src/divide_input.c \
	src/divide_input_helper.c \
	src/env_to_listd.c \
	src/env_to_list_helper.c \
	src/env_to_listd_helper.c \
	src/execute_other.c \
	src/expand_envar_help.c \
	src/expand_envar.c \
	src/free_memory_helper.c \
	src/free_memory.c \
	src/free_memory_help.c \
	src/handle_redir_helper.c \
	src/handle_redirection.c \
	src/one_command.c \
	src/run_commands.c \
	src/run_pipe.c \
	src/separate_tokens_ft_helper.c \
	src/separate_tokens_ft.c \
	src/syntax_error.c \
	src/utils.c \
	src/commands/ft_cd.c \
	src/commands/ft_cd_helper.c \
	src/commands/ft_echo.c \
	src/commands/ft_env.c \
	src/commands/ft_exit.c \
	src/commands/ft_export.c \
	src/commands/ft_export_helper.c \
	src/commands/ft_pwd.c \
	src/commands/ft_unset.c \
	src/commands/buildin_helper.c \
	src/utils/ft_atoi.c \
	src/utils/ft_split.c \
	src/utils/ft_strlcpy.c \
	src/utils/ft_is.c \
	src/utils/ft_itoa.c \
	src/utils/ft_memset.c \
	src/utils/ft_strchr.c \
	src/utils/ft_strcmp.c \
	src/utils/ft_strdup.c \
	src/utils/ft_strjoin.c \
	src/utils/ft_strlen.c \
	src/utils/ft_substr.c \

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
		