/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_listd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:43:22 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 17:15:03 by lmaresov         ###   ########.fr       */
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

t_env	*put_envvar_to_envstruct(char **env_var)
{
	t_env	*env_struct;

	if (!env_var)
	{
		return (NULL);
	}
	env_struct = (t_env *)malloc(sizeof(t_env));
	if (!env_struct)
	{
		return (NULL);
	}
	env_struct->env_key = env_var[0];
	env_struct->env_value = env_var[1];
	return (env_struct);
}

t_listd	*listd_new_node(void *data)
{
	t_listd	*new_node;

	new_node = malloc(sizeof(t_listd));
	if (!new_node)
	{
		return (NULL);
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	listd_add_header(t_listd **listd_header, t_listd *new_node)
{
	new_node->next = *listd_header;
	new_node->prev = NULL;
	if (*listd_header)
	{
		(*listd_header)->prev = new_node;
	}
	*listd_header = new_node;
}

t_listd	*listd_last_node(t_listd *listd_header)
{
	t_listd	*last_node;

	if (!listd_header)
	{
		return (NULL);
	}
	last_node = listd_header;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

void	listd_to_ms(t_listd **listd_header, t_listd *new_node)
{
	t_listd	*last_node;

	if (!*listd_header)
	{
		listd_add_header(listd_header, new_node);
		return ;
	}
	last_node = listd_last_node(*listd_header);
	last_node->next = new_node;
	last_node->prev = last_node;
}

void	add_envv_to_listd(t_ms *ms, t_env *env_struct)
{
	t_listd	*new_node;

	if (!env_struct)
	{
		return ;
	}
	new_node = listd_new_node(env_struct);
	if (!new_node)
	{
		return ;
	}
	listd_to_ms(&ms->envar, new_node);
}

void	env_to_listd(t_ms *ms, char **env)
{
	char	**env_var;
	t_env	*env_struct;

	while (*env)
	{
		env_var = split_env(*env);
		env_struct = put_envvar_to_envstruct(env_var);
		add_envv_to_listd(ms, env_struct);
		env++;
	}
}
