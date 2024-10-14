/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:33 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/14 19:58:27 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void ft_cd_helper(char *path)
{
    if (chdir(path) != 0)
    {
        printf ("chdir error\n");
        return ;
    }
}

void ft_cd(t_ms *ms)
{
    char *path;
    char *temp_key;
    t_listd *tmp_env;

    tmp_env = ms->envar;
    if(!ms->tokens->next)
    {
        path = env_value(ms->envar, "HOME");
        ft_cd_helper(path);
    } 
    else
    {
        path = ms->tokens->next->data;
        ft_cd_helper(path);
    }
    path = (char *)malloc(sizeof(char) * 1024);
    getcwd(path, 1024);
    while(tmp_env)
    {
        temp_key = ((t_env*)tmp_env->data)->env_key;
        //printf ("temp_key: %s\n", temp_key);
        if (strcmp(temp_key, "OLDPWD") == 0)
        {
            free(((t_env*)tmp_env->data)->env_value);
            ((t_env*)tmp_env->data)->env_value = ft_strdup(path);
            return ;
        }
        tmp_env = tmp_env->next;
    }
    //printf ("chyba- preskoceni cyklu while\n");
}

*/
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

int	ft_cd_25(t_ms *ms)
{
	char	*path;

	if (((t_cmd *)ms->commands->data)->arguments[1]
		&& ((t_cmd *)ms->commands->data)->arguments[0])
	{
		printf("function cd takes only one argument\n");
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

void	ft_cd_redir(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = ms->commands->data;
	if (cmd->redir)
	{
		handle_redirection_read(cmd);
		handle_redirection_write(cmd, "");
	}
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
