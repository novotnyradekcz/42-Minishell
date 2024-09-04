/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/04 11:03:14 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int main (int argc, char **argv, char **env)
{
    t_ms *ms;

    ms = malloc(sizeof(t_ms));
    if (!ms)
    {
        printf("malloc ms error");
        return (0);
    }

    if (argc != 1)
    {
        printf("run program ./minishell without arguments\n");
        exit(1);
    }
    ft_memset(ms, '\0', sizeof(t_ms));
    while(1)
    {
        ms->input = get_input(ms);
        if(ft_strcmp(ms->input, "") == 0 || only_whitespace(ms->input))
            continue;
        printf("%s\n", ms->input);
        
        divide_input(ms);
        //return (1);
    }

    //////////////////
    if ( !argv || !env)
    {

    }
    return (0);
}