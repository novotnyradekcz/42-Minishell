/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:02 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 09:46:59 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_env(t_ms *ms, char *key, char *value)
{
	t_listd	*envar;
	t_env	*new_env;
	t_listd	*new_node;

	envar = ms->envar;
	new_env = malloc(sizeof(t_env));
	new_env->env_key = key;
	new_env->env_value = value;
	new_node = malloc(sizeof(t_listd));
	new_node->data = new_env;
	new_node->next = NULL;
	if (!envar)
	{
		ms->envar = new_node;
		new_node->prev = NULL;
	}
	else
	{
		while (envar->next)
		{
			if (ft_strcmp(((t_env *)envar->data)->env_key, key) == 0)
			{
				((t_env *)envar->data)->env_value = value;
				free(key);
				free(new_env);
				free(new_node);
				return ;
			}
			envar = envar->next;
		}
		if (ft_strcmp(((t_env *)envar->data)->env_key, key) == 0)
		{
			((t_env *)envar->data)->env_value = value;
			free(key);
			free(new_env);
			free(new_node);
			return ;
		}
		new_node->prev = envar;
		envar->next = new_node;
	}
}

char	*check_export_arg(char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i])
		i++;
	if (arg[i - 1] == '=')
	{
		key = malloc(sizeof(char) * i);
		ft_strlcpy(key, arg, i);
		return (key);
	}
	return (NULL);
}

char	*check_export_arg2(char *arg)
{
	int		i;
	char	*value;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (NULL);
		i++;
	}
	value = malloc(sizeof(char) * i + 1);
	ft_strlcpy(value, arg, i + 1);
	return (value);
}

void	ft_export(t_ms *ms)
{
	int		i;
	t_listd	*envar;
	char	*key;
	char	*value;
	char	**key_value;

	envar = ms->envar;
	if (!(((t_cmd *)ms->commands->data)->arguments[0]))
	{
		while (envar)
		{
			if (((t_env *)envar->data)->env_value[0] == '\0')
				printf("%s=''\n", ((t_env *)envar->data)->env_key);
			else
				printf("%s=%s\n", ((t_env *)envar->data)->env_key, ((t_env *)envar->data)->env_value);
			envar = envar->next;
		}
		return ;
	}
	i = -1;
	while (((t_cmd *)ms->commands->data)->arguments[++i])
	{
		// check if argument contains '=' at last position
		key = check_export_arg(((t_cmd *)ms->commands->data)->arguments[i]);
		value = NULL;
		if (((t_cmd *)ms->commands->data)->arguments[i + 1])
			value = check_export_arg2(((t_cmd *)ms->commands->data)->arguments[i + 1]);
		if (key)
		{
			if (value)
			{
				set_env(ms, key, value);
				i += 2;
			}

		}
		if(!(((t_cmd *)ms->commands->data)->arguments[i]))
			break ;
		
		key_value = ft_split(((t_cmd *)ms->commands->data)->arguments[i], '=');
		// copy up to '=' to key
		// copy from '=' to end to value
		if (!key_value[1])
			set_env(ms, key_value[0], "");
		else
			set_env(ms, key_value[0], key_value[1]);
		free(key_value);
	}
}
