/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/12 13:10:45 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_ms *ms)
{
	char *exit_code;

	if (!(((t_cmd *)ms->commands->data)->arguments[0]))
	{
		// free memory and exit the minishell
		free_all(ms);
		exit(0);
	}
	if(((t_cmd *)ms->commands->data)->arguments[1])	// check argument list length
	{
		printf("exit: too many arguments\n");
		return ;
	}
	exit_code = ((t_cmd *)ms->commands->data)->arguments[0];
	// if exit_code too long - undefined behaviour (same as bash)
	// free memory and exit the minishell
	free_all(ms);
	exit(ft_atoi(exit_code));
}
