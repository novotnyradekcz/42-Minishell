/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:23:03 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 19:26:09 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_len(char *envv, char sep)
{
	int	i;

	i = 0;
	while (envv[i] != '\0')
	{
		if (envv[i] == sep)
			return (i);
		i++;
	}
	return (0);
}

char	*get_key(char *envv, char sep, int *i, int key_len)
{
	char	*key;
	int		index;

	index = 0;
	key = (char *)malloc(sizeof(char) * key_len + 1);
	if (!key)
	{
		printf("key_malloc_error");
		return (NULL);
	}
	while (envv[*i] != sep)
	{
		key[index] = envv[*i];
		index++;
		(*i)++;
	}
	key[index] = '\0';
	return (key);
}

char	*get_value(char *envv, int *i, int value_len)
{
	char	*value;
	int		index;

	index = 0;
	value = (char *)malloc(sizeof(char) * value_len + 1);
	if (!value)
	{
		printf("value malloc error");
		return (NULL);
	}
	while (envv[*i])
	{
		value[index] = envv[*i];
		index++;
		(*i)++;
	}
	value[index] = '\0';
	return (value);
}

char	**split_key_value(char *envv, char sep)
{
	char	**splited_envar;
	int		i;
	int		envv_len;
	int		key_len;
	int		value_len;

	i = 0;
	envv_len = ft_strlen(envv);
	key_len = get_key_len(envv, sep);
	value_len = envv_len - key_len - 1;
	splited_envar = (char **)malloc(sizeof(char *) * 3);
	if (!splited_envar)
		return (NULL);
	splited_envar[0] = get_key(envv, sep, &i, key_len);
	i++;
	splited_envar[1] = get_value(envv, &i, value_len);
	splited_envar[2] = NULL;
	return (splited_envar);
}

char	**split_env(char *envv)
{
	char	**env_v;

	env_v = split_key_value(envv, '=');
	if (!env_v)
	{
		printf("Error split_key_value");
		return (NULL);
	}
	return (env_v);
}
