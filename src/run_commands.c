/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:11:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/21 09:45:29 by lmaresov         ###   ########.fr       */
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
    else
        return (0);
}


int one_command(t_ms *ms)
{
    if (!ms->tokens->data)
    {
       //printf("CHyba 2\n");
       return (0);
    }    
    if (!check_command(ms->tokens->data))
    {
        printf ("This command is not in options");
        return (0);
    }
    else if (check_command(ms->tokens->data) == 1)
    {
        ft_echo(ms);
    } 
    else if (check_command(ms->tokens->data) == 2)
        ft_cd(ms);
    else if (check_command(ms->tokens->data) == 3)
        ft_pwd(ms);
    /*else if (check_command(ms->tokens->data) == 4)
        ft_export(ms);
    else if (check_command(ms->tokens->data) == 5)
        ft_unset(ms);*/
    else if (check_command(ms->tokens->data) == 6)
        ft_env(ms);
    /*else if (check_command(ms->tokens->data) == 7)
        ft_exit(ms);*/
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