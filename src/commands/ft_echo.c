/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:23:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/21 09:14:26 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_echo_helper(t_list *tmp)
{
    char *str;
    char *tmp_str;

    str = malloc(1);
    if (!str)
        return (NULL);
    str[0] = '\0';
    while (tmp->next)
    {
        tmp_str = ft_strjoin_with_space(str, tmp->data);
        free(str);
        str = tmp_str;
        tmp = tmp->next;
    }
    tmp_str = ft_strjoin(str, tmp->data);
    free(str);
    str = tmp_str;
    return (str);
}

void ft_echo(t_ms *ms)
{
    char *str;
    //char *str_tmp;
    int flag;
    t_list *tmp;


    tmp = ms->tokens->next;
    /*str_tmp = tmp->data;
    printf ("%c,   %c, ", str_tmp[0] , str_tmp[1]);
    if (str_tmp[0] == '-' && str_tmp[1] != 'n')
    {
        printf("invalid option");
        return ;
    }*/
    flag = strcmp(tmp->data, "-n");
    if (flag == 0)
    {
        tmp = tmp->next;
        str = ft_echo_helper(tmp);
        printf("%s", str);
    }
    else
    {
        str = ft_echo_helper(tmp);
        printf("%s\n", str);
    }
}