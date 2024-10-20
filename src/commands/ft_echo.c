/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:23:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 13:08:03 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_echo2(char *argv[])
{
	int	n;
	int	i;
	int	e;

	n = 0;
	e = 0;
	i = 1;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
	{
		n = 1;
		i++;
	}
	if (argv[i])
	{
		e = printf("%s", argv[i]);
		i++;
	}
	while (argv[i] && e >= 0)
	{
		e = printf(" %s", argv[i]);
		i++;
	}
	if (!n && e >= 0)
		e = printf("\n");
	return (e);
}

void	ft_echo(t_ms *ms, char *argv[])
{
	int	e;

	(void)ms;
	e = ft_echo2(argv);
	if (e < 0)
		e = 1;
	else
		e = 0;
	ft_exit(NULL, e);
}
