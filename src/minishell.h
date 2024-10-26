/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:55 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/26 09:55:47 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

#define PROMPT "minishell: "

extern int	g_signal;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_ct
{
	char	**argv;
	char	*hd;
	int		hdpipe[2];
	int		fds[3][2];
}	t_ct;

typedef struct s_cs
{
	int		ctn;
	int		*pids;
	int		(*pipes)[2];
	t_ct	*ct;
}	t_cs;

typedef struct s_ms
{
	int		live;
	int		signal;
	int		parent;
	int		child;
	int		err[2];
	int		error;
	int		exit;
	int		csn;
	char	*prompt;
	char	*pwd;
	char	*s;
	char	**ev;
	t_cs	*cs;
	t_list	*el;
	t_list	*lex;
	t_list	*exe;
}	t_ms;

typedef struct s_ev
{
	char	*s;
	char	*var;
	char	*val;
	char	**vals;
}	t_ev;

typedef struct s_token
{
	unsigned int	type;
	int				csi;
	char			*text;
}	t_token;

typedef enum e_type
{
	SINGLEQUOTE = 1U,
	DOUBLEQUOTE = 2U,
	NOQUOTE = 4U,
	PIPE = 8U,
	INFILE = 16U,
	HEREDOC = 32U,
	OUTFILE = 64U,
	APPEND = 128U,
	ERRFILE = 256U,
	ERRAPPEND = 512U,
	INOUTFILE = 1024U,
	SPACETOKEN = 2048U,
	AND = 4096U,
	OR = 8192U,
	OPENPAR = 16384U,
	CLOSEPAR = 32768U,
	TEXT = 7U,
	REDIRECTS = 2032U,
	ANDOR = 12288U
}	t_type;

typedef struct s_checker
{
	t_token	*token;
	int		text;
	int		stuff;
	int		parentheses;
	int		status;
}	t_check;

// minishell.c
int		minishell(t_ms *ms);

// init.c
void	ft_init(t_ms *ms);
void	ft_init_prompt(t_ms *ms);
t_ev	*ft_init_ev(char *str);
void	sort_env(t_list *el);

// signals.c
void	newline_sig(int signal);
void	global_sig(int signal);
void	new_global_sig(int signal);
void	exit_sig(int signal);

// check/check_tokens_0.c
int		ft_check_token(t_ms *ms);

// check/check_tokens_1.c
void	ft_extra_check_test(t_check *check);
void	ft_extra_check(t_list *lst, t_check *check);
void	ft_check_stuff(t_check *check);
void	ft_check_text(t_check *check);

// commands/ft_cd.c
void	ft_cd(t_ms *ms, char *argv[]);

// commands/ft_echo.c
void	ft_echo(t_ms *ms, char *argv[]);

// commands/ft_env.c
void	ft_env(t_ms *ms, char *argv[]);

// commands/ft_exit.c
void	ft_exit_builtin(t_ms *ms, char *argv[]);

// commands/ft_export.c
void	ft_export(t_ms *ms, char *argv[]);

// commands/ft_pwd.c
void	ft_pwd(t_ms *ms, char *argv[]);

// commands/ft_unset.c
void	ft_unset(t_ms *ms, char *argv[]);

// exec/execute_0.c
int		ft_dup(t_ms *ms, int i, int j);

// exec/execute_1.c
int		ft_executor(t_ms *ms);
int		ft_execcs(t_ms *ms, int i);
int		ft_open_pipes(t_ms *ms, int i);

// exec/execute_2.c
int		ft_exec(t_ms *ms, char **cmd);
void	ft_closefds(t_ms *ms, int i);
void	ft_closepipes(t_ms *ms, int i);
char	*ft_pathjoin(char *path, char *cmd);

// exec/execute_3.c
int		ft_execct(t_ms *ms, int i, int j);

// exec/execute_4.c
void	ft_forking_helper(t_ms *ms, int i, int j);

// exec/execute_5.c
void	ft_heredoc(t_ms *ms, int i, int j);
int		ft_newin(t_ms *ms, int i, int j);
int		ft_newout(t_ms *ms, int i, int j);

// expand/expand_0.c
char	*ft_expand(t_ms *ms, char *s);

// expand/expand_1.c
int		ft_jointext(t_ms *ms);

// expand/expand_2.c
int		ft_expand_strings(t_ms *ms);

// lex/lexer_0.c
t_list	*ft_lexer(t_ms *ms);
void	ft_gettextquote(t_token *token, char **strptr, char quote);
void	ft_getspace(t_token *token, char **strptr);

// lex/lexer_1.c
int		ft_isspace(int c);
int		ft_istoken(int c);
int		ft_isquote(int c);
void	ft_settoken(t_token *token, int type, char *s);
void	ft_gettext(t_token *token, char **strptr);

// lex/lexer_2.c
t_token	*ft_gettoken(char **strptr);

// parse/parser_0.c
int		ft_fillcts(t_ms *ms, int i, int j);
void	ft_updatecsn(t_ms *ms);

// parse/parser_1.c
int		ft_fillctfd(t_ct *ct, char *file, int *r);

// parse/parser_2.c
int		ft_createct(t_ms *ms);
int		ft_parser(t_ms *ms);
int		ft_createcs(t_ms *ms);
void	ft_updatectn(t_ms *ms);

// utils/array_insert.c
int	ft_array_insert(char ***array, char *str, int n);

//	utils/free_0.c
void	ft_free_ev(void *ptr);
void	ft_free_token(void *ptr);
void	ft_free(t_ms *ms);
void	ft_free_cs(t_ms *ms);

//	utils/free_1.c
void	ft_free_array(char ***arrptr);
void	ft_mini_free(t_ms *ms);

// utils/misc.c
void	ft_wait(t_ms *ms, int pid, int options);
void	ft_exit(t_ms *ms, int err);
void	ft_werror(char *s1, char *s2, char *s3);

// utils/envvar.c
char	**ft_list2split(t_list *lst);
char	**ft_getenvvals(t_ms *ms, char *var);
char	*ft_getenvval(t_ms *ms, char *var);
void	ft_changeenvval(t_ms *ms, char *var, char *val);
void	ft_putenv(t_list *el);

#endif