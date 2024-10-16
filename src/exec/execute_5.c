/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:54:56 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/16 14:55:07 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].hd)
		ft_forking_helper(ms, i, j);
}

int	ft_newin(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].fds[0][1] == 2)
		return (ms->cs[i].ct[j].hdpipe[0]);
	if (j)
	{
		if (ms->cs[i].ct[j].fds[0][1] == 1)
			return (ms->cs[i].ct[j].fds[0][0]);
		else
			return (ms->cs[i].pipes[j - 1][0]);
	}
	if (ms->cs[i].ct[j].fds[0][1] == 1)
		return (ms->cs[i].ct[j].fds[0][0]);
	return (0);
}

int	ft_newout(t_ms *ms, int i, int j)
{
	if (j < ms->cs[i].ctn - 1)
	{
		if (ms->cs[i].ct[j].fds[1][1])
			return (ms->cs[i].ct[j].fds[1][0]);
		else
			return (ms->cs[i].pipes[j][1]);
	}
	if (ms->cs[i].ct[j].fds[1][1])
		return (ms->cs[i].ct[j].fds[1][0]);
	return (1);
}
