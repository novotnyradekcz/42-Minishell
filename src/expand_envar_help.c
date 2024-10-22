/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envar_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:02:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 21:53:45 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] == '?')
	{
		key = ft_strdup("?");
		return (key);
	}
	while (ft_isprint(str[i]) && !is_whitespace(str[i]) && str[i] != '\''
		&& str[i] != '\"' && str[i] != '$' && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

t_listd	*get_envar_node(t_listd *envar, char *key)
{
	t_listd	*cur_node;

	cur_node = envar;
	while (cur_node)
	{
		if (ft_strcmp(key, ((t_env *)cur_node->data)->env_key) == 0)
			return (cur_node);
		cur_node = cur_node->next;
	}
	return (NULL);
}

char	*env_value(t_listd *envar, char *key)
{
	t_listd	*envar_node;

	envar_node = get_envar_node(envar, key);
	if (!envar_node)
		return (NULL);
	return (((t_env *)envar_node->data)->env_value);
}

void	no_env_value(t_ms *ms, int *i, char *key)
{
	int		len;
	char	*exp_input;
	char	*exit_code;

	if (ft_strcmp(key, "?") == 0)
	{
		exit_code = ft_itoa(ms->exit_status);
		exp_input = get_exp_input(exit_code, ms->input, *i, *i + 2);
		free(ms->input);
		ms->input = exp_input;
		free(key);
		*i += 2;
		return ;
	}
	len = ft_strlen(key);
	exp_input = get_exp_input("", ms->input, *i, *i + len + 1);
	free(ms->input);
	ms->input = exp_input;
	free(key);
}

char	*get_exp_input(char*value, char*input, int start, int end)
{
	char	*input_begining;
	char	*input_ending;
	char	*tmp;
	char	*new_expanded_input;

	input_begining = ft_substr(input, 0, start);
	input_ending = ft_substr(input, end, ft_strlen(input) - end);
	tmp = ft_strjoin(input_begining, value);
	new_expanded_input = ft_strjoin(tmp, input_ending);
	free(input_begining);
	free(input_ending);
	free(tmp);
	return (new_expanded_input);
}
