/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:59:28 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 12:52:38 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


char * handle_redirection_read(t_cmd * cmd)
{
    char *result;

    result = "nic\n";
    if(ft_strcmp(cmd->redir, "<") == 0)
    {
        result = read_redir(cmd);
        if (ft_strcmp(cmd->command, "cat") == 0)
        {
            //printf("%s", result);
            return(result);
        }    
            
    }
    if(ft_strcmp(cmd->redir, "<<") == 0)
    {
        result = heredoc_redir(cmd);
        //printf("result:%s\n",result);
        return (result);
    }
    return (result);
}


void handle_redirection_write(t_cmd * cmd, char * str)
{
    if(ft_strcmp(cmd->redir, ">") == 0)
        write_redir(cmd, str);
    else if(ft_strcmp(cmd->redir, ">>") == 0)
        append_redir(cmd, str);
}

void handle_redir(t_cmd * cmd, char *str)
{
    if (cmd->redir && (ft_strcmp(cmd->redir, ">") == 0 || ft_strcmp(cmd->redir, ">>") == 0 ))
    {
        handle_redirection_write(cmd, str);
        //printf ("chyba3\n");
    }   
    else if (cmd->redir && (ft_strcmp(cmd->redir, "<") == 0 || ft_strcmp(cmd->redir, "<<") == 0 ))
    {
        handle_redirection_read(cmd);
        //printf ("chyba4\n");
        printf("%s", str);
    }      
}