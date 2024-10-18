/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:36:54 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/18 14:47:04 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putenv(t_list *el)
{
	t_list	*lst;
	t_ev	*ev;

	lst = el;
	while (lst)
	{
		if (lst->content)
		{
			ev = lst->content;
			ft_printf("%s\n", ev->s);
		}
		lst = lst->next;
	}
}

void	ft_changeenvval(t_ms *ms, char *var, char *val)
{
	t_list	*lst;
	t_ev	*ev;
	int		l;

	l = ft_strlen(var);
	lst = ms->el;
	while (lst)
	{
		ev = lst->content;
		if (!ft_strncmp(ev->var, var, l))
		{
			ft_free_split(&ev->vals);
			free(ev->s);
			free(ev->var);
			var = ft_strjoin(var, "=");
			var = ft_strjoin_freeleft(var, val);
			ev->s = var;
			ev->var = ft_strdup(var);
			ev->var[l] = 0;
			ev->val = &ev->var[l + 1];
			ev->vals = ft_split(ev->val, ':');
			return ;
		}
		lst = lst->next;
	}
}

char	*ft_getenvval(t_ms *ms, char *var)
{
	t_list	*lst;
	t_ev	*ev;
	int		l;

	l = ft_strlen(var);
	if (!l)
		return (NULL);
	lst = ms->el;
	while (lst)
	{
		ev = lst->content;
		if (!ft_strncmp(ev->var, var, l))
		{
			return (ev->val);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	**ft_getenvvals(t_ms *ms, char *var)
{
	t_list	*lst;
	t_ev	*ev;
	int		l;

	l = ft_strlen(var);
	if (!l)
		return (NULL);
	lst = ms->el;
	while (lst)
	{
		ev = lst->content;
		if (!ft_strncmp(ev->var, var, l))
		{
			return (ev->vals);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	**ft_list2split(t_list *lst)
{
	int		i;
	char	**env;
	t_ev	*ev;

	i = ft_lstsize(lst);
	env = malloc((sizeof(char *)) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (lst)
	{
		ev = lst->content;
		env[i] = ft_strdup(ev->s);
		i++;
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}
