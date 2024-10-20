/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:56:54 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 12:54:51 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(t_ms *ms)
{
	char	cwd[4096];
	char	*dir;
	char	*home;

	home = ft_getenvval(ms, "HOME");
	dir = getcwd(cwd, 4096);
	if (home && !ft_strncmp(dir, home, ft_strlen(home)))
	{
		dir = dir + (ft_strlen(home) - 1);
		dir[0] = '~';
	}
	ms->prompt = PROMPT;
	ms->prompt = ft_strjoin(ms->prompt, dir);
	ms->prompt = ft_strjoin_freeleft(ms->prompt, " $ ");
}

t_ev	*init_ev(char *str)
{
	t_ev	*ev;
	int		i;

	i = 0;
	ev = malloc(sizeof(t_ev));
	if (!ev)
		return (NULL);
	ev->s = ft_strdup(str);
	ev->var = ft_strdup(str);
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
	ev = init_ev(esplit[0]);
	if (!ev)
		exit(1);
	lstart = ft_lstnew((void *)ev);
	if (!lstart)
		exit(1);
	while (esplit[i])
	{
		ev = init_ev(esplit[i]);
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

void	sort_env(t_list *el)
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

void	ft_init(t_ms *ms)
{
	ms->live = 1;
	ms->parent = 1;
	ms->child = 0;
	ms->signal = 0;
	ms->err[0] = 0;
	ms->err[1] = 0;
	ms->exit = 0;
	ms->error = 0;
	ms->s = NULL;
	ms->csn = 0;
	ms->cs = NULL;
	ms->lex = NULL;
	ms->exe = NULL;
	ms->ev = ft_copy_array(ms->ev);
	ms->el = ft_split2list(ms->ev);
	ft_exit(ms, 0);
	init_prompt(ms);
	sort_env(ms->el);
}
