/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:41 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 15:16:17 by rnovotny         ###   ########.fr       */
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
		ft_printf_fd(2, "env: '%s': Permission denied\n", argv[1]);
		ft_exit(NULL, 126);
	}
	else if (argv[1])
	{
		ft_printf_fd(2, "env: '%s': No such file or directory\n", argv[1]);
		ft_exit(NULL, 127);
	}
	else
	{
		ft_putenv(ms->el);
	}
	ft_exit (NULL, 0);
}
