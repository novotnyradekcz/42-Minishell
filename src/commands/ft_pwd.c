/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:07 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 17:00:51 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_args(char **arguments)
{
	if (arguments[0])
	{
		return (1);
	}
	return (0);
}

void	ft_pwd(t_ms *ms)
{
	char	*cwd;
	t_cmd	*cmd;
	int		original_fd;

	cmd = ms->commands->data;
	if (check_args(((t_cmd *)ms->commands->data)->arguments))
	{
		printf ("pwd: too many arguments\n");
		ms->exit_status = 1;
		return ;
	}
	cwd = (char *)malloc(sizeof(char) * 1024);
	if (!cwd)
	{
		printf("maloc pwd error\n");
		return ;
	}
	if (getcwd(cwd, 1024) != NULL)
	{
		cwd = ft_strjoin(cwd, "\n");
		original_fd = setup_fd(cmd);
		printf("%s", cwd);
		close_fd(cmd, original_fd);
	}
	else
		printf ("error in getcwd function\n");
	free(cwd);
	ms->exit_status = 0;
}
