/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 05:28:42 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/01 09:52:12 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


char *get_input(void)
{
    char *line;
    char *prompt;

    prompt = "minishell>";
    line = readline(prompt);
    if (!line)
    {
        printf("exit\n");
        
        exit(0);
    }
    if (line[0] != '\0')
    {
        add_history(line);
    }
    return(line);
}

int only_whitespace(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (!is_whitespace(str[i]))
            return(0);
        i++;
    }
    return (1);
}

