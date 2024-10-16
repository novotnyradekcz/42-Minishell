/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:29:31 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 12:32:37 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_gettextquote(t_token *token, char **strptr, char quote)
{
	char	*str;
	int		i;

	i = 0;
	(*strptr)++;
	while ((*strptr)[i] && (*strptr)[i] != quote)
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(str, *strptr, i + 1);
	i++;
	while (i)
	{
		(*strptr)++;
		i--;
	}
	if (quote == '\'')
		ft_settoken(token, SINGLEQUOTE, str);
	if (quote == '\"')
		ft_settoken(token, DOUBLEQUOTE, str);
}

void	ft_getspace(t_token *token, char **strptr)
{
	while (ft_isspace(**strptr))
	{
		(*strptr)++;
	}
	ft_settoken(token, SPACETOKEN, NULL);
}

static t_list	*ft_getlst(char **strptr)
{
	t_list	*head;
	t_list	*node;
	t_token	*token;

	token = ft_gettoken(strptr);
	if (!token)
		return (NULL);
	head = ft_lstnew(token);
	if (!head)
		return (NULL);
	token = ft_gettoken(strptr);
	while (token)
	{
		node = ft_lstnew(token);
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		token = ft_gettoken(strptr);
	}
	return (head);
}

t_list	*ft_lexer(t_ms *ms)
{
	t_list	*head;
	char	*str;

	if (!ms->s) 
		return (NULL);
	str = ms->s;
	head = ft_getlst(&str);
	if (!head)
	{
		return (NULL);
	}
	return (head);
}
