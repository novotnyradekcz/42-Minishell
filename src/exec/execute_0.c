/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:11:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 00:35:22 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_newerr(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].fds[2][1])
		return (ms->cs[i].ct[j].fds[2][0]);
	return (2);
}

static int	ft_check_newin(int newin)
{
	if (dup2(newin, STDIN_FILENO) < 0)
	{
		ft_werror("Error duplicating input\n", NULL, NULL);
		return (1);
	}
	else
		return (0);
}

static int	ft_check_newout(int newout)
{
	if (dup2(newout, STDOUT_FILENO) < 0)
	{
		ft_werror("Error duplicating output\n", NULL, NULL);
		return (2);
	}
	else
		return (0);
}

static int	ft_check_newerr(int newerr)
{
	if (dup2(newerr, STDERR_FILENO) < 0)
	{ft_werror("Error duplicating error output\n", NULL, NULL);
		return (3);
	}
	else
		return (0);
}

int	ft_dup(t_ms *ms, int i, int j)
{
	int	newin;
	int	newout;
	int	newerr;

	newin = ft_newin(ms, i, j);
	newout = ft_newout(ms, i, j);
	newerr = ft_newerr(ms, i, j);
	if (newin > 2 && ft_check_newin(newin))
		return (1);
	if (newout > 2 && ft_check_newout(newout))
		return (2);
	if (newerr > 2 && ft_check_newerr(newerr))
		return (3);
	return (0);
}
