/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:33 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/01 06:15:47 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void ft_cd_helper(char *path)
{
    if (chdir(path) != 0)
    {
        printf ("chdir error\n");
        return ;
    }
}

void ft_cd(t_ms *ms)
{
    char *path;
    char *temp_key;
    t_listd *tmp_env;

    tmp_env = ms->envar;
    if(!ms->tokens->next)
    {
        path = env_value(ms->envar, "HOME");
        ft_cd_helper(path);
    } 
    else
    {
        path = ms->tokens->next->data;
        ft_cd_helper(path);
    }
    path = (char *)malloc(sizeof(char) * 1024);
    getcwd(path, 1024);
    while(tmp_env)
    {
        temp_key = ((t_env*)tmp_env->data)->env_key;
        //printf ("temp_key: %s\n", temp_key);
        if (strcmp(temp_key, "OLDPWD") == 0)
        {
            free(((t_env*)tmp_env->data)->env_value);
            ((t_env*)tmp_env->data)->env_value = ft_strdup(path);
            return ;
        }
        tmp_env = tmp_env->next;
    }
    //printf ("chyba- preskoceni cyklu while\n");
}

*/
void ft_cd_helper(char *path)
{
    if (chdir(path) != 0)
    {
        printf ("chdir error\n");
        return ;
    }
}

char *get_args(char ** arguments)
{
    char *str;
    
    str = NULL;
    if(arguments[0])
    {
        str = arguments[0];
        return str;
    }
    return str;
}


void ft_cd(t_ms *ms)
{
    char *path;
    char *temp_key;
    //char *str_tmp;
    t_listd *tmp_env;

    tmp_env = ms->envar;
    if(!get_args(((t_cmd *)ms->commands->data)->arguments))
    {
        path = env_value(ms->envar, "HOME");
        ft_cd_helper(path);
    } 
    else
    {
        
        path = get_args(((t_cmd *)ms->commands->data)->arguments);
        ft_cd_helper(path);
    }
    path = (char *)malloc(sizeof(char) * 1024);
    getcwd(path, 1024);
    while(tmp_env)
    {
        temp_key = ((t_env*)tmp_env->data)->env_key;
        //printf ("temp_key: %s\n", temp_key);
        if (strcmp(temp_key, "OLDPWD") == 0)
        {
            free(((t_env*)tmp_env->data)->env_value);
            ((t_env*)tmp_env->data)->env_value = ft_strdup(path);
            return ;
        }
        tmp_env = tmp_env->next;
    }
    //printf ("chyba- preskoceni cyklu while\n");
}