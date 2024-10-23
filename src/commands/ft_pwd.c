/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:07 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/23 17:47:30 by lmaresov         ###   ########.fr       */
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

void	ft_pwd_helper(t_cmd *cmd)
{
	int		original_fd;
	char	*cwd;
	char	*cwd_1;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (!cwd)
	{
		perror("malloc pwd error");
		return ;
	}
	if (getcwd(cwd, 1024) != NULL)
	{
		cwd_1 = ft_strjoin(cwd, "\n");
		original_fd = setup_fd(cmd);
		printf("%s", cwd_1);
		close_fd(cmd, original_fd);
		free(cwd_1);
	}
	else
		perror("getcwd error");
	free(cwd);
}

void	ft_pwd(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = ms->commands->data;
	if (check_args(((t_cmd *)ms->commands->data)->arguments))
	{
		write(2, "pwd: too many arguments\n", 24);
		ms->exit_status = 1 * 256;
		return ;
	}
	ft_pwd_helper(cmd);
	ms->exit_status = 0;
}
