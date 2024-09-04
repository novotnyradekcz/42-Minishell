/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:29:31 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/04 12:08:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void divide_input(t_ms *ms)
{
    separate_tokens(ms, ms->input);

//
//
//
//
}

void separate_tokens(t_ms *ms, char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == ' ' || !ft_isprint(input[i]))
            i++;
        else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
        {
            redirection_token(ms, input, &i);
            //printf("redirection token a%sa\n", (char*)ms->tokens->next->next->data);
        }
        else if (input[i] == '\'' || input[i] == '\"')
        {
            quotation_marks_token(ms, input, &i);
            //printf("quotation mark token a%sa\n", (char*)ms->tokens->next->data);
        }
        else
        {
            remaining_arg_token(ms, input, &i);
            //printf("remaining token a%sa\n", (char*)ms->tokens->data);
        }
            
    }
}

