/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 05:28:42 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 11:50:43 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *get_input_heredoc(char *eof)
{
    char *line;
    char *prompt;
    char *new_line;
    char *temp;

    line = malloc(sizeof(char));
    new_line= "";
    temp = "";
    line[0] = '\0';
    while (ft_strcmp(eof, line) != 0)
    {
        free(line);
        prompt = "heredoc>";
        line = readline(prompt);
        if (!line)
        {
            printf("exit\n");
            return(0);
        }
        if (ft_strcmp(eof, line) != 0)
        {
            temp = ft_strjoin(line, "\n");
            new_line = ft_strjoin(new_line, temp);
            free(temp);
        }      
    }
    free(line);
    return(new_line);
}


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

