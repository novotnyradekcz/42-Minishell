/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/12 11:20:08 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_from_env(t_ms *ms, t_listd *envar, char *key)
{
	t_listd	*tmp;
	t_listd	*prev;

	tmp = envar;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->data)->env_key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				ms->envar = tmp->next;
			free(tmp->data);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_ms *ms)
{
	t_listd	*envar;

	envar = ms->envar;
	if (!ms->tokens->next)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	if (!envar)
		return ;
	while (ms->tokens->next)
	{
		rm_from_env(ms, envar, ms->tokens->next->data);
	}
}
