/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 05:27:00 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/23 18:29:53 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_var(t_env *env)
{
	if (env->env_key)
		free(env->env_key);
	if (env->env_value)
		free(env->env_value);
}

void	free_ms_envar(t_listd *envar)
{
	t_listd	*tmp;

	while (envar)
	{
		tmp = envar->next;
		if (envar->data)
		{
			free_env_var((t_env *)envar->data);
			free(envar->data);
		}
		free(envar);
		envar = tmp;
	}
}

void	free_path_array(char **path_array)
{
	int	i;

	i = 0;
	if (path_array)
	{
		while (path_array[i])
			free(path_array[i++]);
		free(path_array);
	}
}

void	ft_free_ae(char **arg, char **env)
{
	free_args(arg);
	free_args(env);
}
