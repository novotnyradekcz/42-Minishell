/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:02:34 by rnovotny          #+#    #+#             */
/*   Updated: 2024/09/19 12:00:11 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <signal.h>
# include <stdio.h>

int		g_signal;

typedef struct s_minishell
{
	int		running;
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
	char	**env;
	t_cs	*cs;
	t_list	*envlist;
	t_list	*lex;
	t_list	*exe;
}	t_minishell;

#endif
