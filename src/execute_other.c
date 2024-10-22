/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:44:16 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 16:21:09 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_i(t_listd *envar)
{
	t_listd	*cur_node;
	int		i;

	cur_node = envar;
	i = 0;
	while (cur_node)
	{
		i++;
		cur_node = cur_node->next;
	}
	return (i);
}

char	**env_to_char(t_listd *envar)
{
	t_listd	*cur_node;
	char	**env;
	int		i;

	i = get_i(envar);
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	cur_node = envar;
	while (cur_node)
	{
		env[i] = ft_strdup(((t_env *)cur_node->data)->env_key);
		env[i] = ft_strjoin_freeleft(env[i], "=");
		env[i] = ft_strjoin_freeleft(env[i],
				((t_env *)cur_node->data)->env_value);
		i++;
		cur_node = cur_node->next;
	}
	env[i] = NULL;
	return (env);
}

int	check_exec_or_dir(char *path)
{
	if (ft_strchr(path, '/') != NULL && (path[0] == '/' || path[0] == '.'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*get_path(char **path_array, char *command)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(tmp, command);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	child_process(t_ms *ms, char **env, char **arg)
{
	char	*path;
	char	**path_array;

	if (check_exec_or_dir(arg[0]))
	{
		path = ft_strdup(arg[0]);
	}
	else
	{
		path_array = ft_split(env_value(ms->envar, "PATH"), ':');
		path = get_path(path_array, arg[0]);
		free_path_array(path_array);
	}
	if (!path)
	{
		ms->exit_status = 127;
		exit(127);
	}
	execve(path, arg, env);
	free(path);
}
