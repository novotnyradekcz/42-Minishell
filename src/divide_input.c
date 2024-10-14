/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:29:31 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/14 18:14:47 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char **get_arguments(t_cmd *curr_cmd, t_ms *ms)
{
    char **args;
    char **tmp;
    int num_of_args;
    int i;
    
    num_of_args = 0;
    args = (char **)malloc(sizeof(char*));
    args[0] = NULL;
    while(ms->tokens && (ft_strcmp((char *)ms->tokens->data, "|") != 0))
    {
        if (ft_strcmp((char *)ms->tokens->data, ">") == 0 || ft_strcmp((char *)ms->tokens->data, ">>") == 0)
        {
            curr_cmd->redir = ft_strdup((char *)ms->tokens->data);
            curr_cmd->redir_file = ft_strdup((char *)ms->tokens->next->data);
            ms->tokens = ms->tokens->next;
            return args;
        }
        else if (ft_strcmp((char *)ms->tokens->data, "<") == 0 || ft_strcmp((char *)ms->tokens->data, "<<") == 0)
        {
            curr_cmd->redir = ft_strdup((char *)ms->tokens->data);
            curr_cmd->redir_file = ft_strdup((char *)ms->tokens->next->data);
            ms->tokens = ms->tokens->next;
            return args;
        }
        num_of_args++;
        tmp = (char **)malloc(sizeof(char *) * (num_of_args + 1));
        if (!tmp)
            return NULL;
        i = 0;
        while (args[i])
        {
            tmp[i] = ft_strdup(args[i]);
            free(args[i]);
            i++;
        }
        tmp[i] = ft_strdup((char *)ms->tokens->data);
        tmp[i + 1] = NULL;
        free(args);
        args = tmp;
        ms->tokens = ms->tokens->next;
    }
    curr_cmd->num_of_args = num_of_args;
    return args;
}

void init_cmd(t_cmd *cmd)
{
    cmd->arguments = NULL;
    cmd->command = NULL;
    cmd->here_doc = NULL;
    cmd->num_of_args = 0;
    cmd->option = NULL;
    cmd->redir = NULL;
    cmd->redir_file = NULL;
}

t_cmd *get_one_cmd(t_ms * ms)
{
    t_cmd *curr_cmd;
    char **arguments;

    curr_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    init_cmd(curr_cmd);
    arguments = NULL;
    curr_cmd->command = ft_strdup((char *)ms->tokens->data);
    if (ms->tokens->next && (ft_strcmp((char *)ms->tokens->data, "echo") == 0) && (ft_strcmp((char *)ms->tokens->next->data, "-n") == 0))
    {
        ms->tokens = ms->tokens->next;
        curr_cmd->option = ft_strdup((char *)ms->tokens->data);
    }
    ms->tokens = ms->tokens->next;
    arguments = get_arguments(curr_cmd, ms);
    curr_cmd->arguments = arguments;
    return curr_cmd;
}

void put_node_to_ms(t_list **header, t_list *new_node)
{
    t_list *last_node;
    
    if (!*header)
    {
        new_node->next = *header;
        *header = new_node;
        return ;
    }
    last_node = *header;
    while ( last_node->next)
        last_node = last_node->next;
    last_node->next = new_node;
    new_node->next = 0;
} 

void divide_commands(t_ms *ms)
{
    t_list *new_node;
    t_cmd *one_cmd;
    while (ms->tokens && (ft_strcmp((char *)ms->tokens->data, "|") != 0))
    {
        
        new_node = (t_list *)malloc(sizeof(t_list));
        if (!new_node)
            return;
        one_cmd = get_one_cmd(ms);
        
        new_node->data = (void *)one_cmd;
        new_node->next = NULL;
        put_node_to_ms(&(ms->commands), new_node);
       
    }
    if (ms->tokens && ft_strcmp((char *)ms->tokens->data, "|") == 0)
    {
        ms->tokens = ms->tokens->next;
    }
}

void divide_input(t_ms *ms)
{
    expand_envar(ms);
    //printf("ms->input after expanding envvar: %s\n", ms->input);
   // return ;
    separate_tokens(ms, ms->input);
    while (ms->tokens)
    {
        divide_commands(ms);
        if (ms->tokens && ft_strcmp((char *)ms->tokens->data, "|") == 0)
        {
            ms->tokens = ms->tokens->next; 
        }
    }
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
        {
            //printf("chyba\n");
            get_envar(ms, &i);
            //printf("chyba2\n");
        }
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

