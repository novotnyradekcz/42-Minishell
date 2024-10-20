/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_tokens_ft_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:58:15 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 23:42:02 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_to_list(t_ms *ms, int start, int end)
{
	char	*input_substr;
	t_list	*new_token;

	input_substr = ft_substr(ms->input, start, end - start);
	new_token = save_token(input_substr);
	add_token_to_mstokens(&(ms->tokens), new_token);
}

t_list	*save_token(char *data)
{
	t_list	*new_token;

	new_token = malloc(sizeof(t_list));
	if (!new_token)
	{
		return (NULL);
	}
	new_token->data = data;
	new_token->next = 0;
	return (new_token);
}

void	add_token_to_mstokens(t_list **header, t_list *new_token)
{
	t_list	*last_token;

	if (!*header)
	{
		new_token->next = *header;
		*header = new_token;
		return ;
	}
	last_token = *header;
	while (last_token->next)
		last_token = last_token->next;
	last_token->next = new_token;
	new_token->next = 0;
}

int	only_remain_char_checker(char c)
{
	char	*excluded_chars;

	excluded_chars = "><|\'\"";
	if (ft_strchr(excluded_chars, c))
		return (0);
	else if (!ft_isprint(c))
		return (0);
	else if (c == ' ')
		return (0);
	else
		return (1);
}
