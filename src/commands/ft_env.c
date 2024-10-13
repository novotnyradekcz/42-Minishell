/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:41 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 10:41:26 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_args(char **arguments)
{
    if (arguments[0])
    {
        return 1;
    }
    return 0;
}

char *env_str(char *env_key, char *env_value)
{
    char *new_str;
    char *tmp;
    char *temp;

    //printf("key: %s, value: %s\n", env_key, env_value);
    tmp = ft_strjoin(env_key, "=");
    //printf("tmp: %s\n", tmp);
    temp = ft_strjoin(tmp, env_value);
    new_str = ft_strjoin(temp, "\n");
    //printf("new_str: %s\n", new_str);
    free(tmp);
    free(temp);
   
    return (new_str);
}

char *all_env_str(t_listd *tmp, char *new_str)
{
    char *temp_env_key;
    char *temp_env_value;
    char *temp_str;

    temp_env_key = ((t_env *)tmp->data)->env_key;
    temp_env_value = ((t_env *)tmp->data)->env_value;
    temp_str = env_str(temp_env_key, temp_env_value);
        //printf("new_str: %s\n", temp_str);
    new_str = ft_strjoin(new_str, temp_str);
        //printf("new_str2: %s\n", new_str);
    free(temp_str);
    return (new_str);
}

void ft_env(t_ms *ms)
{
    t_listd *tmp;
    //char *temp_env_key;
    //char *temp_env_value;
    char *new_str;
    //char *temp_str;
    t_cmd * cmd;
    
    new_str = malloc(sizeof(char));
    new_str = "\0";
    
    if (check_args(((t_cmd *)ms->commands->data)->arguments))
    {
        printf("run env without arguments\n");
        return ;
    }
    tmp = ms->envar;
    while (tmp->next)
    {
        new_str = all_env_str(tmp, new_str);
        //printf("%s=%s\n", temp_env_key, temp_env_value);
        tmp = tmp->next;
    }
    new_str = all_env_str(tmp, new_str);
    cmd = ms->commands->data;
    if (cmd->redir && (ft_strcmp(cmd->redir, ">") == 0 || ft_strcmp(cmd->redir, ">>") == 0 ))
    {
        handle_redirection_write(cmd, new_str);
    }    
    else
        printf("%s", new_str);
}