/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:39:40 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/19 12:24:39 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_replacetilda(t_ms *ms, char *s, int *i)
{
	char	*strstart;
	char	*strend;
	char	*home;

	home = ft_getenvval(ms, "HOME");
	if (home)
		strend = ft_strdup((&s[(*i) + 1]));
	else
		return (s);
	s[*i] = 0;
	strstart = ft_strdup((s));
	s = ft_strjoin(strstart, home);
	s = ft_strjoin_freeleft(s, strend);
	free(strend);
	free(strstart);
	*i += ft_strlen(home) - 1;
	return (s);
}

static char	*ft_expand_tilda(t_ms *ms, char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '~')
			s = ft_replacetilda(ms, s, &i);
		i++;
	}
	return (s);
}

static int	ft_expand_strings_helper(t_ms *ms, t_token *token)
{
	char	*str;

	str = token->text;
	if (token->type == NOQUOTE || token->type == DOUBLEQUOTE)
	{
		if (token->type == NOQUOTE)
		{
			token->text = ft_expand_tilda(ms, str);
			if (token->text != str && str)
				free(str);
			if (!token->text)
				return (1);
		}
		str = token->text;
		token->text = ft_expand(ms, str);
		if (token->text != str && str)
			free(str);
		if (!token->text)
			return (1);
	}
	return (0);
}

int	ft_expand_strings(t_ms *ms)
{
	t_list	*lst;
	t_token	*token;

	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		if (ft_expand_strings_helper(ms, token))
			return (1);
		// if (token->type == NOQUOTE)
		// 	ft_expand_wild(ms, lst);
		lst = lst->next;
	}
	return (0);
}
