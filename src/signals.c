/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:18:58 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/20 12:40:31 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newline_sig(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	global_sig(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
	}
}

void	new_global_sig(int signal)
{
	write(1, "\n", 1);
	if (signal == SIGINT)
		exit(130);
}

void	exit_sig(int signal)
{
	if (signal == SIGINT)
		exit(130);
}
