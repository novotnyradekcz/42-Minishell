/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:59:46 by rnovotny          #+#    #+#             */
/*   Updated: 2024/09/07 17:00:04 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_newline(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	ft_global_sig(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
	}
}

void	ft_newglobal_sig(int signal)
{
	write(1, "\n", 1);
	if (signal == SIGINT)
		exit(130);
}

void	ft_exit_sig(int signal)
{
	if (signal == SIGINT)
		exit(130);
}
