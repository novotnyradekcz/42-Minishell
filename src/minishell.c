/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 15:57:44 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	ft_errorcheck(t_ms *ms)
{
	if (ms->err[1])
		ms->err[1] = 0;
	else if (ms->err[0])
		ms->err[0] = 0;
}

void	ft_analyse(t_ms *ms)
{
	ms->lex = ft_lexer(ms);
	if (ft_tokenchecker(ms))
		return ;
	if (ft_parser(ms))
		perror("Unexpected token or something bad\n");
	if (ft_bonus_executor(ms))
		perror("Executor error\n");
}

int	minishell(t_ms *ms)
{
	while (ms->live)
	{
		signal(SIGINT, ft_newline);
		ms->s = readline(ms->prompt);
		if (!ms->s)
			break ;
		else
		{
			if (ms->s[0])
				add_history (ms->s);
			ft_analyse(ms);
			ft_errorcheck(ms);
			free(ms->s);
			ft_mini_free(ms);
		}
	}
	write(1, "exit\n", 5);
	ft_free(ms);
	return (ms->exit);
}

int main (int argc, char **argv, char **env)
{
    t_ms	ms;

	(void)argc;
	(void)argv;
	g_signal = 0;
	ms.ev = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_newline);
	ft_init(&ms);
	minishell(&ms);
	return (ms.exit);
}