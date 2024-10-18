/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:00:56 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 19:21:00 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arguments_helper(t_cmd *curr_cmd, t_ms *ms)
{
	if (ft_strcmp((char *)ms->tokens->data, ">") == 0
		|| ft_strcmp((char *)ms->tokens->data, ">>") == 0)
	{
		curr_cmd->redir = ft_strdup((char *)ms->tokens->data);
		curr_cmd->redir_file = ft_strdup((char *)ms->tokens->next->data);
		ms->tokens = ms->tokens->next;
		return (1);
	}
	else if (ft_strcmp((char *)ms->tokens->data, "<") == 0
		|| ft_strcmp((char *)ms->tokens->data, "<<") == 0)
	{
		curr_cmd->redir = ft_strdup((char *)ms->tokens->data);
		curr_cmd->redir_file = ft_strdup((char *)ms->tokens->next->data);
		ms->tokens = ms->tokens->next;
		return (1);
	}
	return (0);
}

char	**get_args_helper(int num_of_args, char **args, t_ms *ms)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (num_of_args + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (args[i])
	{
		tmp[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	tmp[i] = ft_strdup((char *)ms->tokens->data);
	tmp[i + 1] = NULL;
	free(args);
	args = tmp;
	return (args);
}

char	**get_arguments(t_cmd *curr_cmd, t_ms *ms)
{
	char	**args;
	int		num_of_args;

	num_of_args = 0;
	args = (char **)malloc(sizeof(char *));
	args[0] = NULL;
	while (ms->tokens && (ft_strcmp((char *)ms->tokens->data, "|") != 0))
	{
		if (get_arguments_helper(curr_cmd, ms))
			return (args);
		num_of_args++;
		args = get_args_helper(num_of_args, args, ms);
		if (!args)
			return (NULL);
		ms->tokens = ms->tokens->next;
	}
	curr_cmd->num_of_args = num_of_args;
	return (args);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->arguments = NULL;
	cmd->command = NULL;
	cmd->here_doc = NULL;
	cmd->num_of_args = 0;
	cmd->option = NULL;
	cmd->redir = NULL;
	cmd->redir_file = NULL;
}

t_cmd	*get_one_cmd(t_ms *ms)
{
	t_cmd	*curr_cmd;
	char	**arguments;

	curr_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	init_cmd(curr_cmd);
	arguments = NULL;
	curr_cmd->command = ft_strdup((char *)ms->tokens->data);
	if (ms->tokens->next
		&& (ft_strcmp((char *)ms->tokens->data, "echo") == 0)
		&& (ft_strcmp((char *)ms->tokens->next->data, "-n") == 0))
	{
		ms->tokens = ms->tokens->next;
		curr_cmd->option = ft_strdup((char *)ms->tokens->data);
	}
	ms->tokens = ms->tokens->next;
	arguments = get_arguments(curr_cmd, ms);
	curr_cmd->arguments = arguments;
	return (curr_cmd);
}
