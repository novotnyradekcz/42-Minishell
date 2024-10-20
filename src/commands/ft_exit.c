/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 11:13:11 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_builtin(t_ms *ms, char *argv[])
{
	ms->live = 0;
	if (argv[1])
	{
		ms->exit = ft_atoi(argv[1]) % 256;
		ms->live = 0;
		if (argv[2])
		{
			ms->exit = 0;
			ms->live = 1;
			ms->error = 1;
			write(2, "minishell: exit: too many arguments\n", 36);
		}
	}
}
