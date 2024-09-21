/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:34:07 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/21 09:37:20 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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