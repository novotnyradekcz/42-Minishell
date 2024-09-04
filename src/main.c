/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:01:27 by rnovotny          #+#    #+#             */
/*   Updated: 2024/09/01 07:09:27 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	check(t_minishell *minishell)
{
	if (minishell->err[1])
		minishell->err[1] = 0;
	else if (minishell->err[0])
		minishell->err[0] = 0;
}

void	parse(t_minishell *minishell)
{
	minishell->lex = ft_lexer(minishell);
	if (ft_tokenchecker(minishell))
		return ;
	if (ft_parser(minishell))
		ft_printf_fd(2, "Unexpected token or something bad\n");
	if (ft_bonus_executor(minishell))
		ft_printf_fd(2, "Executor error\n");
}

int	loop(t_minishell *minishell)
{
	while (minishell->running)
	{
		signal(SIGINT, ft_newline);
		minishell->s = readline(minishell->prompt);
		if (!minishell->s)
			break ;
		else
		{
			if (minishell->s[0])
				add_history (minishell->s);
			parse(minishell);
			check(minishell);
			free(minishell->s);
			ft_mini_free(minishell);
		}
	}
	write(1, "exit\n", 5);
	ft_free(minishell);
	return (minishell->exit);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	g_signal = 0;
	minishell.env = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_newline);
	ft_init(&minishell);
	loop(&minishell);
	return (minishell.exit);
}