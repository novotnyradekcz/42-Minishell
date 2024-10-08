/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:41 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/01 06:22:04 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_args(char **arguments)
{
    if (arguments[0])
    {
        return 1;
    }
    return 0;
}

void ft_env(t_ms *ms)
{
    t_listd *tmp;
    char *temp_env_key;
    char *temp_env_value;
    
    if (check_args(((t_cmd *)ms->commands->data)->arguments))
    {
        printf("run env without arguments\n");
        return ;
    }
    tmp = ms->envar;
    while (tmp->next)
    {
        temp_env_key = ((t_env *)tmp->data)->env_key;
        temp_env_value = ((t_env *)tmp->data)->env_value;
        printf("%s=%s\n", temp_env_key, temp_env_value);
        tmp = tmp->next;
    }
}