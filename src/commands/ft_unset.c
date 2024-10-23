/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/23 20:42:20 by lmaresov         ###   ########.fr       */
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
		write(2, "unset: not enough arguments\n", 28);
		ms->exit_status = 1 * 256;
		return ;
	}
	if (!envar)
		return ;
	i = -1;
	while (((t_cmd *)ms->commands->data)->arguments[++i])
		rm_from_env(ms, ((t_cmd *)ms->commands->data)->arguments[i]);
	ms->exit_status = 0;
}
