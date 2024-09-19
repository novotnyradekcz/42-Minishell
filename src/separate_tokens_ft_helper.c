/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_tokens_ft_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:58:15 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/19 06:28:16 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void add_token_to_list(t_ms *ms, int start, int end)
{
    char *input_substr;
    t_list *new_token;
    printf("ms inpput:%s\n", ms->input);
    input_substr = ft_substr(ms->input, start, end-start);
    printf ("input_substr: %s\n", input_substr);
    new_token = save_token(input_substr);
    add_token_to_mstokens(&(ms->tokens), new_token);
}
/*
t_list *create_new_token(void *data)
{
    t_list *new_token;
    
    new_token = malloc(sizeof(t_list));
    if(!new_token)
        return(NULL);
    new_token->data = data;
    new_token->next = 0; 
    
    return (new_token);

}
*/

/*
t_list last_token(t_list *header)
{
    t_list *last_token;

    last_token = header;
    while (last_token->next)
        last_token = last_token->next;
    return (last_token);
}
*/
t_list *save_token(char *data)
{
    t_list *new_token;

    new_token = malloc(sizeof(t_list));
    if(!new_token)
    {
        ////////
        return(NULL);
    }
    ft_memset(new_token, '\0', sizeof(t_list));
    new_token->data = data;
    new_token->next = 0;    
    return(new_token);
}

void add_token_to_mstokens(t_list **header, t_list *new_token)
{
    t_list *last_token;

    if (!*header)
    {
        new_token->next = *header;
        *header = new_token;
        return ;
    }
    last_token = *header;
    while (last_token->next)
        last_token = last_token->next;
    last_token->next = new_token;
    new_token->next = 0;
}

int only_remain_char_checker(char c)
{
    char *excluded_chars;

    excluded_chars = "><|\'\"";
    if (ft_strchr(excluded_chars, c))
        return (0);
    else if (!ft_isprint(c))
        return (0);
    /*else if (is_whitespace(c))
        return (0);*/
    else if (c == ' ')
        return (0);
    else    
        return (1);
}
