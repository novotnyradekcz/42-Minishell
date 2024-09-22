/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/22 10:03:53 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_ms *ms)
{
	char *exit_code;

	if(!ms->tokens->next)
	{
		// free memory and exit the minishell
		exit(0);
	}
	if(ms->tokens->next->next)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	exit_code = ms->tokens->next->data;
	// if exit_code too long - undefined behaviour (same as bash)
	// free memory and exit the minishell
	exit(ft_atoi(exit_code));
}
