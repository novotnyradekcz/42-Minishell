/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:11:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/12 13:06:09 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_command(char *command)
{
    if(strcmp(command, "echo") == 0)
      return (1);
    else if (strcmp(command, "cd") == 0)
        return (2);
    else if (strcmp(command, "pwd") == 0)
        return (3);
    else if (strcmp(command, "export") == 0)
        return (4);
    else if (strcmp(command, "unset") == 0)
        return (5);
    else if (strcmp(command, "env") == 0)
        return (6);
    else if (strcmp(command, "exit") == 0)
        return (7);
    else if (strcmp(command, "cat") == 0)
        return (8);
    else
        return (0);
}


int one_command(t_ms *ms)
{
    if (!ms->commands->data)
    {
       //printf("CHyba 2\n");
       return (0);
    }    
    if (!check_command(((t_cmd *)ms->commands->data)->command))
    {
        printf ("This command is not in options\n");
        return (0);
    }
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 1)
    {
        ft_echo(ms);
    } 
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 2)
        ft_cd(ms);
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 3)
        ft_pwd(ms);
    /*else if (check_command(ms->tokens->data) == 4)
        ft_export(ms);
    else if (check_command(ms->tokens->data) == 5)
        ft_unset(ms);*/
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 6)
        ft_env(ms);
    /*else if (check_command(ms->tokens->data) == 7)
        ft_exit(ms);*/
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 8)
        ft_cat(ms);
    return (1);   
}

/*void more_commands(t_ms *ms)
{
    
}*/

void run_commands(t_ms *ms)
{
    
    if (ms->num_of_cmd == 1)
    {
        //printf("Chyba 1\n");
        one_command(ms);
    }
    /*else if (ms->num_of_cmd > 1)
    {
        more_commands(ms);
    }*/
}