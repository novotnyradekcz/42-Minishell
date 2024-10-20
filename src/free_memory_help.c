/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:35:22 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 13:57:08 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_args(t_cmd *cmd)
{
	int	i;

	if (cmd->command)
		free(cmd->command);
	if (cmd->arguments)
	{
		i = 0;
		while (cmd->arguments[i])
		{
			free(cmd->arguments[i]);
			i++;
		}
		free(cmd->arguments);
	}
}

void	free_ms_commands(t_ms *ms)
{
	t_list	*current_node;
	t_list	*next_node;
	t_cmd	*cmd;

	current_node = ms->commands;
	while (current_node)
	{
		cmd = (t_cmd *)current_node->data;
		free_cmd_args(cmd);
		if (cmd->redir)
			free(cmd->redir);
		if (cmd->redir_file)
			free(cmd->redir_file);
		free(cmd);
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	ms->commands = NULL;
}

int	free_tmp(char **tmp, int i)
{
	while (--i >= 0)
		free(tmp[i]);
	free(tmp);
	return (0);
}

void	free_no_input(t_ms *ms)
{
	if (ms)
	{
		if (ms->envar)
			free_ms_envar(ms->envar);
		free(ms);
	}
}
