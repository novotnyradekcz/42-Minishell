/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 05:22:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 17:29:50 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ms_input(t_ms *ms)
{
	if (ms->input)
	{
		free(ms->input);
		ms->input = NULL;
	}
	ms->double_quotes = 0;
	ms->single_quotes = 0;
	ms->num_of_cmd = 1;
}

void	free_ms_tokens(t_ms *ms)
{
	if (ms->tokens)
	{
		del_tokens(&ms->tokens);
		ms->tokens = NULL;
	}
}

void	free_ms_commands(t_ms *ms)
{
	t_list	*current_node;
	t_list	*next_node;
	t_cmd	*cmd;
	int		i;

	current_node = ms->commands;
	while (current_node)
	{
		cmd = (t_cmd *)current_node->data;
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

void	free_ms_envar(t_listd **header)
{
	if (!header || !*header)
	{
		printf("error: free_ms_envar");
		return ;
	}
	while (*header)
	{
		del_header_listd(header);
	}
}

void	free_all(t_ms *ms)
{
	if (ms)
	{
		free_ms_input(ms);
		free_ms_tokens(ms);
		if (ms->envar)
		{
			free_ms_envar(&ms->envar);
			ms->envar = NULL;
		}
		free(ms);
	}
}
