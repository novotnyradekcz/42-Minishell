/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:18:24 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/23 20:27:08 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_value(t_listd *envar, t_listd *new_node, char *key, char *value)
{
	free(((t_env *)envar->data)->env_value);
	((t_env *)envar->data)->env_value = value;
	free(key);
	free(new_node->data);
	free(new_node);
}

t_listd	*update_env(t_ms *ms, t_listd *new_node, char *key, char *value)
{
	t_listd	*envar;

	envar = ms->envar;
	while (envar->next)
	{
		if (ft_strcmp(((t_env *)envar->data)->env_key, key) == 0)
		{
			replace_value(envar, new_node, key, value);
			return (NULL);
		}
		envar = envar->next;
	}
	if (ft_strcmp(((t_env *)envar->data)->env_key, key) == 0)
	{
		replace_value(envar, new_node, key, value);
		return (NULL);
	}
	return (envar);
}

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
		envar = update_env(ms, new_node, key, value);
		if (!envar)
			return ;
		new_node->prev = envar;
		envar->next = new_node;
	}
}
