/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:59:28 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 19:38:51 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void	handle_redirection_read(t_cmd * cmd)
{
    if(ft_strcmp(cmd->redir, "<") == 0)
    {
        read_redir(cmd);
    }
    if(ft_strcmp(cmd->redir, "<<") == 0)
    {
        printf("chyba handle_redirection_read\n");
        heredoc_redir(cmd);
        
        //printf("result:%s\n",result);
        return ;
    }
}


void handle_redirection_write(t_cmd * cmd)
{
    if(ft_strcmp(cmd->redir, ">") == 0)
        write_redir(cmd);
    else if(ft_strcmp(cmd->redir, ">>") == 0)
        append_redir(cmd);
}

void handle_redir(t_cmd * cmd)
{
    if (cmd->redir && (ft_strcmp(cmd->redir, ">") == 0 || ft_strcmp(cmd->redir, ">>") == 0 ))
    {
        handle_redirection_write(cmd);
        printf ("chyba3\n");
    }   
    else if (cmd->redir && (ft_strcmp(cmd->redir, "<") == 0 || ft_strcmp(cmd->redir, "<<") == 0 ))
    {
        handle_redirection_read(cmd);
        printf ("chyba4\n");
    }      
}