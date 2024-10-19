/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 05:22:57 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 17:37:23 by lmaresov         ###   ########.fr       */
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
