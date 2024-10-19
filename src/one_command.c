/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:44:29 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 11:53:27 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	else if (strcmp(command, "cd") == 0)
		return (2);
	else if (strcmp(command, "pwd") == 0)
		return (3);
	else if (strcmp(command, "export") == 0)
		return (4);
	else if (strcmp(command, "unset") == 0)
		return (5);
	else if (strcmp(command, "env") == 0)
		return (6);
	else if (strcmp(command, "exit") == 0)
		return (7);
	else
		return (0);
}

int	one_command(t_ms *ms)
{
	if (!ms->commands->data)
		return (0);
	if (!check_command(((t_cmd *)ms->commands->data)->command))
	{
		printf ("This command is not in options\n");
		return (0);
	}
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 1)
		ft_echo(ms);
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 2)
		ft_cd(ms);
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 3)
		ft_pwd(ms);
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 4)
		ft_export(ms);
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 5)
		ft_unset(ms);
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 6)
		ft_env(ms);
	else if (check_command(((t_cmd *)ms->commands->data)->command) == 7)
		ft_exit(ms);
	return (1);
}
