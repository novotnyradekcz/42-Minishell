/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:02 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 23:32:25 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_ms *ms)
{
	t_listd	*envar;

	envar = ms->envar;
	while (envar)
	{
		if (((t_env *)envar->data)->env_value[0] == '\0'
			|| ft_strchr(((t_env *)envar->data)->env_value, ' '))
			printf("%s='%s'\n", ((t_env *)envar->data)->env_key,
				((t_env *)envar->data)->env_value);
		else
			printf("%s=%s\n", ((t_env *)envar->data)->env_key,
				((t_env *)envar->data)->env_value);
		envar = envar->next;
	}
	ms->exit_status = 0;
	return ;
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

char	**process_export(t_ms *ms, int *i, char	**args)
{
	char	*key;
	char	*value;
	char	**key_value;

	key = check_export_arg(args[*i]);
	value = args[*i + 1];
	if (value)
		value = check_export_arg2(value);
	if (key && value)
	{
		set_env(ms, key, value);
		*i += 2;
	}
	if (!(args[*i]))
		return (NULL);
	key_value = ft_split(args[*i], '=');
	return (key_value);
}

void	ft_export(t_ms *ms)
{
	int		i;
	char	**key_value;

	if (!(((t_cmd *)ms->commands->data)->arguments[0]))
		print_export(ms);
	i = -1;
	while (((t_cmd *)ms->commands->data)->arguments[++i])
	{
		key_value = process_export(ms, &i,
				((t_cmd *)ms->commands->data)->arguments);
		if (!key_value)
			break ;
		if (!key_value[1])
		{
			key_value[1] = malloc(sizeof(char));
			key_value[1][0] = '\0';
		}
		set_env(ms, key_value[0], key_value[1]);
		free(key_value);
	}
	ms->exit_status = 0;
}
