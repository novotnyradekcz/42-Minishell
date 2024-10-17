/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:02:38 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 16:32:50 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_ms *ms)
{
	char	*command;

	command = ((t_cmd *)ms->commands->data)->command;
	if (!ft_strcmp(command, "echo"))
		return (1);
	else if (!ft_strcmp(command, "cd"))
		return (1);
	else if (!ft_strcmp(command, "pwd"))
		return (1);
	else if (!ft_strcmp(command, "export"))
		return (1);
	else if (!ft_strcmp(command, "unset"))
		return (1);
	else if (!ft_strcmp(command, "env"))
		return (1);
	else if (!ft_strcmp(command, "exit"))
		return (1);
	else
		return (0);
}
