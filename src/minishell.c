/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/19 15:00:05 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        rl_replace_line("", 0);
        printf("\n");
        //printf("\n Caught SIGINT (Crtl +C)\n");
        rl_on_new_line();
        rl_redisplay();
    }
}

void allocate_memory(t_ms **ms, size_t size, char *message)
{
    *ms = malloc(size);
    if (!*ms)
    {
        printf("%s\n", message);
        return ;
    }
    ft_memset(*ms, '\0', size);
}


int main (int argc, char **argv, char **env)
{
    t_ms *ms;

    if (argc != 1)
    {
        printf("run program ./minishell without arguments\n");
        exit(1);
    }
    allocate_memory(&ms, sizeof(t_ms), "Error: ms malloc");
    /*
    ms = malloc(sizeof(t_ms));
    if (!ms)
    {
        printf("malloc ms error");
        free(ms);
        return (0);
    }
    ft_memset(ms, '\0', sizeof(t_ms));*/
    signal(SIGINT, ft_handle_signal);
    signal(SIGQUIT, SIG_IGN);
    env_to_listd(ms, env);
    while(1)
    {
        ms->input = get_input();
        if(ft_strcmp(ms->input, "") == 0 || only_whitespace(ms->input))
            continue;
        //printf("%s\n", ms->input);
        
        divide_input(ms);
        //return (1);
    }

    //////////////////
    if ( !argv || !env)
    {

    }
    return (0);
}