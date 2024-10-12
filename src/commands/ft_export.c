/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:02 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/12 13:26:45 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_ms *ms)
{
	int		i;
	t_listd	*envar;
	t_env	*new_env;
	t_listd	*new_node;

	envar = ms->envar;
	if (!(((t_cmd *)ms->commands->data)->arguments[0]))
	{
		while (envar)
		{
			printf("%s=\"%s\"\n", ((t_env *)envar->data)->env_key, ((t_env *)envar->data)->env_value);
			envar = envar->next;
		}
		return ;
	}
	i = 0;
	while (((t_cmd *)ms->commands->data)->arguments[i++])
	{
		new_env = malloc(sizeof(t_env));
		new_env->env_key = ms->tokens->next->data;
		new_env->env_value = NULL;
		new_node = malloc(sizeof(t_listd));
		new_node->data = new_env;
		new_node->next = NULL;
		if (!envar)
		{
			ms->envar = new_node;
			envar = ms->envar;
		}
		else
		{
			while (envar->next)
				envar = envar->next;
			envar->next = new_node;
		}
		ms->tokens = ms->tokens->next;
	}
}
