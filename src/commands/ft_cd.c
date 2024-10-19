/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:33 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 16:50:03 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_redir(t_ms *ms)
{
	t_cmd	*cmd;
	int		original_fd;

	cmd = ms->commands->data;
	if (cmd->redir)
	{
		if (ft_strcmp(cmd->redir, ">") == 0
			|| ft_strcmp(cmd->redir, ">>") == 0)
			original_fd = dup(STDOUT_FILENO);
		else if (ft_strcmp(cmd->redir, "<") == 0
			|| ft_strcmp(cmd->redir, "<<") == 0)
			original_fd = dup(STDIN_FILENO);
		handle_redir(cmd);
	}
	close_fd(cmd, original_fd);
}

char	*get_path_variable(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * 1024);
	getcwd(path, 1024);
	return (path);
}

void	ft_cd(t_ms *ms)
{
	char	*path;
	char	*temp_key;
	t_listd	*tmp_env;

	ft_cd_redir(ms);
	if (ft_cd_25(ms))
		return ;
	tmp_env = ms->envar;
	path = get_path_variable();
	while (tmp_env)
	{
		temp_key = ((t_env *)tmp_env->data)->env_key;
		if (strcmp(temp_key, "OLDPWD") == 0)
		{
			free(((t_env *)tmp_env->data)->env_value);
			((t_env *)tmp_env->data)->env_value = ft_strdup(path);
			ms->exit_status = 0;
			return ;
		}
		tmp_env = tmp_env->next;
	}
	free(path);
}
