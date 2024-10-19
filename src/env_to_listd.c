/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_listd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:43:22 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 19:28:34 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
