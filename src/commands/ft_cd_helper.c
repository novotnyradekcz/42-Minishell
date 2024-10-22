/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:37:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 22:06:07 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_helper(char *path, t_ms *ms)
{
	if (chdir(path) != 0)
	{
		printf ("chdir error\n");
		ms->exit_status = 1;
		return (1);
	}
	return (0);
}

int	ft_cd_25(t_ms *ms)
{
	char	*path;

	if (((t_cmd *)ms->commands->data)->arguments[1]
		&& ((t_cmd *)ms->commands->data)->arguments[0])
	{
		write(2, "cd: too many arguments\n", 23);
		ms->exit_status = 1;
		return (1);
	}
	if (!get_args(((t_cmd *)ms->commands->data)->arguments))
	{
		path = env_value(ms->envar, "HOME");
		if (ft_cd_helper(path, ms))
			return (1);
	}
	else
	{
		path = get_args(((t_cmd *)ms->commands->data)->arguments);
		if (ft_cd_helper(path, ms))
			return (1);
	}
	return (0);
}

char	*get_args(char **arguments)
{
	char	*str;

	str = NULL;
	if (arguments[0])
	{
		str = arguments[0];
		return (str);
	}
	return (str);
}

char	*check_num_args(char **arguments)
{
	char	*str;

	str = NULL;
	if (arguments[1])
	{
		str = arguments[1];
		return (str);
	}
	return (str);
}
