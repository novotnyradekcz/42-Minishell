/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:55 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/01 11:18:29 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>



typedef struct s_list t_list;

typedef struct s_list
{
    t_list *next;
    void *data;
} t_list;

typedef struct s_ms
{
    char *input;
    t_list *tokens;
}t_ms;

typedef struct s_env
{
    char *env_key;
    char *env_value;
}t_env;

//divide_input.c
void divide_input(t_ms *ms);
void separate_tokens(t_ms *ms, char *input);

//separate_tokens_ft.c
void redirection_token(t_ms *ms, char *input, int *i);
void quotation_marks_token(t_ms*ms, char *input, int *i);
void remaining_arg_token(t_ms *ms, char *input, int *i);

//separate_tokens_ft_helper.c
void add_token_to_list(t_ms *ms, int start, int end);
t_list *save_token(char *data);
void add_token_to_mstokens(t_list **header, t_list *new_token);
int only_remain_char_checker(char c);

//utils.c
char *get_input();
int only_whitespace(char *str);


//ft_libft.c
int	ft_isascii(int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int	ft_isprint(int c);
int is_whitespace(int c);
void	*ft_memset(void *s, int c, size_t n);

#endif