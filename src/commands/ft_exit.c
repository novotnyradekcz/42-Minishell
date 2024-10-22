/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 16:56:42 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_ms *ms)
{
	int	exit_code;

	if (!(((t_cmd *)ms->commands->data)->arguments[0]))
	{
		free_all(ms);
		exit(0);
	}
	if (((t_cmd *)ms->commands->data)->arguments[1])
	{
		printf("exit: too many arguments\n");
		return ;
	}
	exit_code = ft_atoi(((t_cmd *)ms->commands->data)->arguments[0]);
	free_all(ms);
	exit(exit_code);
}
/* if exit_code too long - undefined behaviour (same as bash) */
