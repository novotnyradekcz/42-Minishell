/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 10:23:42 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_from_env(t_ms *ms, char *key)
{
	t_listd	*envar;
	t_listd	*prev;

	envar = ms->envar;
	prev = NULL;
	while (envar)
	{
		if (!(ft_strcmp(((t_env *)envar->data)->env_key, key)))
		{
			if (prev)
				prev->next = envar->next;
			else
				ms->envar = envar->next;
			free(((t_env *)envar->data)->env_key);
			if (((t_env *)envar->data)->env_value[0])
				free(((t_env *)envar->data)->env_value);
			free(envar->data);
			free(envar);
			return ;
		}
		prev = envar;
		envar = envar->next;
	}
}

void	ft_unset(t_ms *ms)
{
	int		i;
	t_listd	*envar;

	envar = ms->envar;
	if (!(((t_cmd *)ms->commands->data)->arguments[0]))
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	if (!envar)
		return ;
	i = -1;
	while (((t_cmd *)ms->commands->data)->arguments[++i])
		rm_from_env(ms, ((t_cmd *)ms->commands->data)->arguments[i]);
}
