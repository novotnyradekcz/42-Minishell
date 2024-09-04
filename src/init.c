/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 07:32:05 by rnovotny          #+#    #+#             */
/*   Updated: 2024/09/01 11:19:21 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_prompt(t_ms *ms)
{
	char	cwd[4096];
	char	*s;
	char	*h;

	h = ft_getenvval(ms, "HOME");
	s = getcwd(cwd, 4096);
	if (h && !ft_strncmp(s, h, ft_strlen(h)))
	{
		s = s + (ft_strlen(h) - 1);
		s[0] = '~';
	}
	ms->prompt = ft_strjoin(PROMPT1, PROMPT2);
	ms->prompt = ft_strjoin_freeleft(ms->prompt, s);
	ms->prompt = ft_strjoin_freeleft(ms->prompt, PROMPT3);
}

t_ev	*ft_evinit(char *str)
{
	t_ev	*ev;
	int		i;

	i = 0;
	ev = malloc(sizeof(t_ev));
	if (!ev)
		return (NULL);
	ev->s = ft_stringcopy(str);
	ev->var = ft_stringcopy(str);
	while (ev->var[i] && ev->var[i] != '=')
		i++;
	if (ev->var[i] == '=')
	{
		ev->val = &ev->var[i + 1];
		ev->var[i] = 0;
	}
	else
		ev->val = NULL;
	ev->vals = ft_split(ev->val, ':');
	return (ev);
}

static t_list	*ft_split2list(char **esplit)
{
	int		i;
	t_list	*lstart;
	t_list	*lst;
	t_ev	*ev;

	i = 1;
	ev = ft_evinit(esplit[0]);
	if (!ev)
		exit(1);
	lstart = ft_lstnew((void *)ev);
	if (!lstart)
		exit(1);
	while (esplit[i])
	{
		ev = ft_evinit(esplit[i]);
		if (!ev)
			exit(1);
		lst = ft_lstnew((void *)ev);
		if (!lst)
			exit(1);
		ft_lstadd_back(&lstart, lst);
		i++;
	}
	return (lstart);
}

void	ft_sortenv(t_list *el)
{
	int		sort;
	t_list	*lst;
	t_ev	*enow;
	t_ev	*enext;

	sort = 1;
	while (sort)
	{
		sort = 0;
		lst = el;
		while (lst->next)
		{
			enow = lst->content;
			if (lst->next)
				enext = lst->next->content;
			if (ft_strncmp(enow->var, enext->var, 1024) > 0)
			{
				lst->content = enext;
				lst->next->content = enow;
				sort = 1;
			}
			lst = lst->next;
		}
	}
}

void	init(t_minishell *minishell)
{
	minishell->live = 1;
	minishell->parent = 1;
	minishell->child = 0;
	minishell->signal = 0;
	minishell->err[0] = 0;
	minishell->err[1] = 0;
	minishell->exit = 0;
	minishell->error = 0;
	minishell->s = NULL;
	minishell->csn = 0;
	minishell->cs = NULL;
	minishell->lex = NULL;
	minishell->exe = NULL;
	minishell->env = ft_copy_split(minishell->env);
	minishell->envlist = ft_split2list(minishell->env);
	ft_exit(ms, 0);
	ft_init_prompt(ms);
	ft_sortenv(minishell->envlist);
}
