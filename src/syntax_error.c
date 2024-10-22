/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:56:54 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 22:34:14 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_int_init_helper(t_ms *ms, int i)
{
	if (ms->input[i] == '\"')
	{
		ms->double_quotes++;
		i++;
		while (ms->input[i] != '\0' && ms->input[i] != '\"')
			i++;
		if (ms->input[i] == '\"')
			ms->double_quotes++;
	}
	else if (ms->input[i] == '\'')
	{
		ms->single_quotes++;
		i++;
		while (ms->input[i] != '\0' && ms->input[i] != '\'')
			i++;
		if (ms->input[i] == '\'')
			ms->single_quotes++;
	}
	else if (ms->input[i] == '|' && ms->input[i - 1] != '\\')
		ms->num_of_cmd++;
	return (i);
}

void	ms_int_init(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->input[i])
	{
		while (is_whitespace(ms->input[i]))
			i++;
		i = ms_int_init_helper(ms, i);
		if (ms->input[i])
			i++;
	}
}

int	check_pipes(t_ms *ms)
{
	int		i;
	char	cur_char;

	i = 0;
	while (is_whitespace(ms->input[i]))
		i++;
	if (ms->input[i] == '|')
		return (1);
	while (ms->input[i])
	{
		while (is_whitespace(ms->input[i]))
			i++;
		cur_char = ms->input[i];
		while (is_whitespace(ms->input[i + 1]))
			i++;
		i++;
		if (ms->input[i] == '\0' && cur_char == '|')
		{
			return (1);
		}
	}
	return (0);
}

int	check_redir(t_ms *ms)
{
	int		i;
	char	cur_char;

	i = 0;
	while (is_whitespace(ms->input[i]))
		i++;
	if (ms->input[i] == '>' || ms->input[i] == '<')
		return (1);
	while (ms->input[i])
	{
		while (is_whitespace(ms->input[i]))
			i++;
		cur_char = ms->input[i];
		while (is_whitespace(ms->input[i + 1]))
			i++;
		i++;
		if (ms->input[i] == '\0' && (cur_char == '<' || cur_char == '>'))
		{
			return (1);
		}
	}
	return (0);
}

int	syntax_error(t_ms *ms)
{
	ms_int_init(ms);
	if (ms->double_quotes % 2 != 0 || ms->single_quotes % 2 != 0)
	{
		write(2, "\nclose the quote in the comand\n", 31);
		free_ms_input(ms);
		return (1);
	}
	if (ms->num_of_cmd > 1 && check_pipes(ms))
	{
		write(2, "comand line cannot start or end with | \n", 40);
		free_ms_input(ms);
		return (1);
	}
	if (check_redir(ms))
	{
		write(2, "command line cannot start or end with redirection \n", 51);
		free_ms_input(ms);
		return (1);
	}
	return (0);
}
