/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:29:31 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/23 21:00:53 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_node_to_ms(t_list **header, t_list *new_node)
{
	t_list	*last_node;

	if (!*header)
	{
		new_node->next = *header;
		*header = new_node;
		return ;
	}
	last_node = *header;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
	new_node->next = 0;
}

void	divide_commands(t_ms *ms)
{
	t_list	*new_node;
	t_cmd	*one_cmd;
	t_list	*tmp;

	while (ms->tokens && (ft_strcmp((char *)ms->tokens->data, "|") != 0))
	{
		new_node = (t_list *)malloc(sizeof(t_list));
		if (!new_node)
			return ;
		one_cmd = get_one_cmd(ms);
		new_node->data = (void *)one_cmd;
		new_node->next = NULL;
		put_node_to_ms(&(ms->commands), new_node);
	}
	if (ms->tokens && ft_strcmp((char *)ms->tokens->data, "|") == 0)
	{
		tmp = ms->tokens->next;
		free_token_node(ms->tokens);
		ms->tokens = tmp;
	}
}

void	divide_input(t_ms *ms)
{
	t_list	*tmp;

	expand_envar(ms);
	separate_tokens(ms, ms->input);
	while (ms->tokens)
	{
		divide_commands(ms);
		if (ms->tokens && ft_strcmp((char *)ms->tokens->data, "|") == 0)
		{
			tmp = ms->tokens->next;
			free_token_node(ms->tokens);
			ms->tokens = tmp;
		}
	}
}

void	expand_envar(t_ms *ms)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (ms->input[i])
	{
		quote_checker(ms->input[i], &quote);
		if ((quote == 0 || quote == 2) && ms->input[i] == '$')
		{
			get_envar(ms, &i);
		}
		else
			i++;
	}
}

void	separate_tokens(t_ms *ms, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || !ft_isprint(input[i]))
			i++;
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			redirection_token(ms, input, &i);
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			quotation_marks_token(ms, input, &i);
		}
		else
		{
			remaining_arg_token(ms, input, &i);
		}
	}
}
