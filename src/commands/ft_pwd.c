/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:07 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 10:46:40 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
/*
void ft_pwd(t_ms *ms)
{
    char *cwd;
    
    if (ms->tokens->next)
    {
        printf ("run pwd without arguments\n");
        return ;
    }
    cwd = (char *)malloc(sizeof(char) * 1024);
    if (!cwd)
    {
        printf("maloc pwd error\n");
        return ;
    }
    if (getcwd(cwd, 1024) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        printf ("error in getcwd function\n");
    }
    free(cwd);
}
*/
static int check_args(char **arguments)
{
    if (arguments[0])
    {
        return 1;
    }
    return 0;
}

void ft_pwd(t_ms *ms)
{
    char *cwd;
    t_cmd *cmd;

    cmd = ms->commands->data;
    if (check_args(((t_cmd *)ms->commands->data)->arguments))
    {
        printf ("run pwd without arguments\n");
        return ;
    }
    cwd = (char *)malloc(sizeof(char) * 1024);
    if (!cwd)
    {
        printf("maloc pwd error\n");
        return ;
    }
    if (getcwd(cwd, 1024) != NULL)
    {
        if (cmd->redir && (ft_strcmp(cmd->redir, ">") == 0 || ft_strcmp(cmd->redir, ">>") == 0 ))
            handle_redirection_write(cmd, cwd);
        else
            printf("%s\n", cwd);
    }
    else
        printf ("error in getcwd function\n");
    free(cwd);
}
