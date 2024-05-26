# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/26 10:03:59 by rnovotny          #+#    #+#              #
#    Updated: 2024/05/26 10:04:01 by rnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c

OBJS := ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re