/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_listd_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:24 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 19:28:16 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
