/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/12 10:53:47 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        rl_replace_line("", 0);
        printf("\n");
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

void init_ms(t_ms *ms, char **env)
{
    env_to_listd(ms, env);
    ms->num_of_cmd = 1;
    ms->double_quotes = 0;
    ms->single_quotes = 0;
}



int main (int argc, char **argv, char **env)
{
    t_ms *ms;

    if (argc != 1)
    {
        printf("run program ./minishell without arguments\n");
        exit(1);
    }
    signal(SIGINT, ft_handle_signal);
    signal(SIGQUIT, SIG_IGN);
    allocate_memory(&ms, sizeof(t_ms), "Error: ms malloc");
    init_ms(ms, env);
    while(1)
    {
        ms->input = get_input();
        if(ft_strcmp(ms->input, "") == 0 || only_whitespace(ms->input))
            continue;
        if (syntax_error(ms))
            continue;
        divide_input(ms);
        run_commands(ms);
        //printf("num of comands: %d\n", ms->num_of_cmd);
        //printf("double quotes: %d\n", ms->double_quotes);
        //printf("single quotes: %d\n", ms->single_quotes);
        //printf("%s\n", (char*)ms->envar->data);
        free_ms_input(ms);
        free_ms_tokens(ms);
    }

    //////////////////
    if ( !argv)
    {

    }
    return (0);
}