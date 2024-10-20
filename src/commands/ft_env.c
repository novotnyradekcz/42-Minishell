/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:41 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 00:40:15 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_ms *ms, char *argv[])
{
	if (!argv[1])
	{
		ft_putenv(ms->el);
		ft_exit (NULL, 0);
	}
	if (!(access(argv[1], F_OK)))
	{
		ft_werror("env: ", argv[1], ": Permission denied\n");
		ft_exit(NULL, 126);
	}
	else if (argv[1])
	{
		ft_werror("env: ", argv[1], ": No such file or directory\n");
		ft_exit(NULL, 127);
	}
	else
	{
		ft_putenv(ms->el);
	}
	ft_exit (NULL, 0);
}
