/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:55 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/30 08:25:55 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



typedef struct s_list t_list;
typedef struct s_listd t_listd;

typedef struct s_list
{
    t_list *next;
    void *data;
} t_list;

typedef struct s_listd
{
    void * data;
    t_listd *prev;
    t_listd *next;
    
}t_listd;

typedef struct s_ms
{
    char *input;
    t_list *tokens;
    t_listd *envar;
    t_list *commands;
    int num_of_cmd;
    int single_quotes;
    int double_quotes;
    
}t_ms;

typedef struct s_env
{
    char *env_key;
    char *env_value;
    
}t_env;

typedef struct s_cmd
{
    char *command;
    char **arguments;
    char *redir;
    int num_of_args;
    char *redir_file;
    char *here_doc;
    char *option;
}t_cmd;


//divide_input.c
void divide_input(t_ms *ms);
void expand_envar(t_ms *ms);
void separate_tokens(t_ms *ms, char *input);

//env_to_listd.c
int get_key_len(char *envv, char sep);
char *get_key(char *envv, char sep, int *i, int key_len);
char *get_value(char *envv, int *i, int value_len);
char **split_key_value(char *envv, char sep);
char **split_env(char *envv);
t_env * put_envvar_to_envstruct(char ** env_var);
t_listd *listd_new_node(void *data);
void listd_add_header(t_listd **listd_header, t_listd *new_node);
t_listd * listd_last_node(t_listd *listd_header);
void listd_to_ms(t_listd ** listd_header, t_listd *new_node);
void add_envv_to_listd(t_ms *ms, t_env *env_struct);
void env_to_listd(t_ms *ms, char **env);


//expand_envar_help.c
char *env_key(char *str);
t_listd *get_envar_node(t_listd *envar, char *key);
char *env_value(t_listd *envar, char *key);
void no_env_value(t_ms *ms, int *i, char *key);
char *get_exp_input(char*value, char*input, int start, int end);

//expand_envar.c
void quote_checker(char character, int *quote);
void get_envar(t_ms *ms, int *i);

//free_memory_helper.c
void free_header_ptr(void **ptr);
void del_header_list(t_list **header);
void del_tokens(t_list **header);
void del_header_listd(t_listd **header);


//free_memory.c
void free_ms_input(t_ms *ms);
void free_ms_tokens(t_ms *ms);
void free_ms_envar(t_listd **header);
void free_all(t_ms *ms);
void free_ms_commands(t_ms *ms);


//ft_libft.c
int	ft_isascii(int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int	ft_isprint(int c);
int is_whitespace(int c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_with_space(char const *s1, char const *s2);
char	*ft_strdup(const char *s);


//run_comands.c
int check_command(char *command);
int one_command(t_ms *ms);


void run_commands(t_ms *ms);





//separate_tokens_ft_helper.c
void add_token_to_list(t_ms *ms, int start, int end);
t_list *save_token(char *data);
void add_token_to_mstokens(t_list **header, t_list *new_token);
int only_remain_char_checker(char c);

//separate_tokens_ft.c
void redirection_token(t_ms *ms, char *input, int *i);
void quotation_marks_token(t_ms*ms, char *input, int *i);
void remaining_arg_token(t_ms *ms, char *input, int *i);

//syntax_error.c
int syntax_error(t_ms *ms);

//utils.c
char *get_input();
int only_whitespace(char *str);

//commands/ft_echo.c
void ft_echo(t_ms *ms);

//commands/ft_env.c
void ft_env(t_ms *ms);

//commands/ft_pwd.c
void ft_pwd(t_ms *ms);

//commands/ft_cd.c
void ft_cd(t_ms *ms);

#endif