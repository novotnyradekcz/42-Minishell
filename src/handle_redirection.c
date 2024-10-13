/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:59:28 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 10:49:44 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void handle_redirection_read(t_cmd * cmd)
{
    char *result;

    result = "nic\n";
    if(ft_strcmp(cmd->redir, "<") == 0)
    {
        result = read_redir(cmd);
        if (ft_strcmp(cmd->command, "cat") == 0)
            printf("%s", result);
    }
    if(ft_strcmp(cmd->redir, "<<") == 0)
    {
        result = heredoc_redir(cmd);
    }
}


void handle_redirection_write(t_cmd * cmd, char * str)
{
    if(ft_strcmp(cmd->redir, ">") == 0)
        write_redir(cmd, str);
    else if(ft_strcmp(cmd->redir, ">>") == 0)
        append_redir(cmd, str);
}