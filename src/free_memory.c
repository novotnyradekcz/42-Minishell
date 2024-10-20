/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 05:22:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 23:42:51 by rnovotny         ###   ########.fr       */
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
	t_list	*tmp;
	t_list	*tokens;

	tokens = ms->tokens;
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->data)
		{
			free(tokens->data);
			tokens->data = NULL;
		}
		free(tokens);
		tokens = tmp;
	}
	ms->tokens = NULL;
}

void	free_one_input(t_ms *ms)
{
	free_ms_input(ms);
	free_ms_tokens(ms);
	free_ms_commands(ms);
}

void	free_all(t_ms *ms)
{
	if (ms)
	{
		if (ms->input)
			free(ms->input);
		if (ms->tokens)
		{
			free_ms_tokens(ms);
		}
		if (ms->commands)
			free_ms_commands(ms);
		if (ms->envar)
			free_ms_envar(ms->envar);
		free(ms);
	}
}
