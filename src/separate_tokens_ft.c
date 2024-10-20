/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_tokens_ft.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:57:55 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 20:32:29 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_token(t_ms *ms, char *input, int *i)
{
	if (input[*i] == '>' || input[*i] == '<')
	{
		if (input[*i] == input[*i + 1])
		{
			add_token_to_list(ms, *i, *i + 2);
			(*i) += 2;
		}
		else
		{
			add_token_to_list(ms, *i, *i + 1);
			(*i) += 1;
		}
	}
	else if (input[*i] == '|')
	{
		add_token_to_list(ms, *i, *i + 1);
		(*i) += 1;
	}
}

void	quotation_marks_token(t_ms*ms, char *input, int *i)
{
	char	quotation_mark;
	int		start;
	int		end;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quotation_mark = input[*i];
		(*i)++;
		start = *i;
		while (input[*i] != quotation_mark)
		{
			(*i)++;
		}
		end = (*i);
		add_token_to_list(ms, start, end);
		(*i)++;
	}
}

void	remaining_arg_token(t_ms *ms, char *input, int *i)
{
	int	start;
	int	end;

	if (only_remain_char_checker(input[*i]))
	{
		start = (*i);
		(*i)++;
		while (only_remain_char_checker(input[*i]))
		{
			(*i)++;
		}
		end = (*i);
		add_token_to_list(ms, start, end);
	}
}
