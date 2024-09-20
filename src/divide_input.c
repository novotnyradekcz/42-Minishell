/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:29:31 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/20 06:54:17 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void divide_input(t_ms *ms)
{
    expand_envar(ms);
    //printf("ms->input after expanding envvar: %s\n", ms->input);
    separate_tokens(ms, ms->input);
    
//
//
//
//
}

void expand_envar(t_ms *ms)
{
    int quote;
    int i;
    
    i = 0;
    quote = 0;
    while (ms->input[i])
    {
        quote_checker(ms->input[i], &quote);
        if ((quote == 0 || quote == 2) && ms->input[i] == '$')
            get_envar(ms, &i);
        else
            i++;
    }
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
            /*if (input[i] == '|')
                (ms->num_of_cmd)++;*/
            redirection_token(ms, input, &i);
            
            
            ////
            /*printf("redirection token a%sa\n", (char*)ms->tokens->next->next->data);
            if (ms->tokens && ms->tokens->next && ms->tokens->next->data)
            {
                printf("redirection mark token a%sa\n", (char*)ms->tokens->next->data);
            } 
            if (ms->tokens && ms->tokens->next && ms->tokens->next->next  && ms->tokens->next->next->data)
            {
                printf("redirection mark token a%sa\n", (char*)ms->tokens->next->next->data);
            }*/
        }
        else if (input[i] == '\'' || input[i] == '\"')
        {
            quotation_marks_token(ms, input, &i);
            
            ////
            /*printf("quotation mark token a%sa\n", (char*)ms->tokens->data);
            if (ms->tokens && ms->tokens->next && ms->tokens->next->data)
            {
                printf("quotation mark token a%sa\n", (char*)ms->tokens->next->data);
            } 
            if (ms->tokens && ms->tokens->next && ms->tokens->next->next  && ms->tokens->next->next->data)
            {
                printf("quotation mark token a%sa\n", (char*)ms->tokens->next->next->data);
            }*/
        }
        else
        {
            remaining_arg_token(ms, input, &i);
            
            ////
            /*printf("remaining token a%sa\n", (char*)ms->tokens->data);
            if (ms->tokens && ms->tokens->next && ms->tokens->next->data)
            {
                printf("remaining token a%sa\n", (char*)ms->tokens->next->data);
            } 
            if (ms->tokens && ms->tokens->next && ms->tokens->next->next  && ms->tokens->next->next->data)
            {
                printf("remaining token a%sa\n", (char*)ms->tokens->next->next->data);
            }*/
        }
            
    }
}

