/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:01:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 08:09:53 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_fillct_helper(t_ct *ct, char *text)
{
	if (!ct->argv && text)
	{
		ct->argv = malloc(sizeof(char *) * 2);
		if (!ct->argv)
			return (1);
		ct->argv[0] = ft_strdup(text);
		if (!ct->argv[0])
			return (1);
		ct->argv[1] = NULL;
	}
	else if (ct->argv && text)
	{
		if (array_insert(&ct->argv, text, ft_array_len(ct->argv)))
		{
			printf("err3\n");
			return (1);
		}
	}
	return (0);
}

int	ft_fillct(t_ct *ct, char *text, int *r)
{
	if (!(*r))
	{
		if (ft_fillct_helper(ct, text))
			return (1);
	}
	else
	{
		if (ft_fillctfd(ct, text, r))
			return (2);
	}
	return (0);
}

static t_list	*ft_fillcts_init(t_ms *ms, int *i, int *j, int *r)
{
	*i = 0;
	*j = 0;
	*r = 0;
	return (ms->lex);
}

int	ft_fillcts(t_ms *ms, int i, int j)
{
	t_list	*lst;
	t_token	*token;
	int		r;

	lst = ft_fillcts_init(ms, &i, &j, &r);
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
		{
			j = 0;
			i++;
			ms->cs[i].ct[j].argv = NULL;
		}
		else if (token->type & PIPE)
			j++;
		else if (token->type & REDIRECTS)
			r = token->type & REDIRECTS;
		else if (token->type & TEXT)
			if (ft_fillct(&(ms->cs[i].ct[j]), token->text, &r))
				return (1);
		lst = lst->next;
	}
	return (0);
}

void	ft_updatecsn(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;

	i = 0;
	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
			i++;
		token->type |= 0x10000U * i;
		lst = lst->next;
	}
	ms->csn = i + 1;
}
