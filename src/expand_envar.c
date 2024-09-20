/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:01:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/20 06:46:54 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void quote_checker(char character, int *quote)
{
    if (*quote == 0)
    {
        if (character == '\'')
            *quote = 1;
        else if (character == '\"')
            *quote = 2;
    }
    else if (*quote == 1 && character == '\'')
        *quote = 0;
    else if (*quote == 2 && character == '\"')
        *quote = 0;
}

void get_envar(t_ms *ms, int *i)
{
    char *key;
    char *value;
    int len;
    char *exp_input;

    key = env_key(ms->input + *i + 1);
    //printf("key: %s\n", key);
    value = env_value(ms->envar, key);
    //printf("value: %s\n", value);
    if (!value)
    {
        no_env_value(ms, i, key);
    }
    else
    {
        len = ft_strlen(key);
        exp_input = get_exp_input(value, ms->input, *i, (*i + len + 1));
        free (ms->input);
        ms->input = exp_input;
        *i = *i + ft_strlen(value);
    }
}
