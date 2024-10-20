/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 05:27:00 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 08:44:58 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait(t_ms *ms, int pid, int options)
{
	int		err;

	waitpid(pid, &err, options);
	ms->parent--;
	if (WIFEXITED(err))
	{
		ms->error = WEXITSTATUS(err);
	}
	else if (WIFSIGNALED(err))
	{
		if (WTERMSIG(err) == g_signal)
		{
			write(1, "\n", 1);
			g_signal = 0;
		}
		else if (WTERMSIG(err) == SIGQUIT)
			write(1, "\n", 1);
	}
	else
	{
		ms->error = 0;
	}
	if (g_signal)
		g_signal = 0;
}

void	ft_exit(t_ms *ms, int err)
{
	static t_ms	*stat;

	if (!stat)
		stat = ms;
	else
	{
		ft_free(stat);
		exit(err);
	}
}

void	ft_werror(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
}
