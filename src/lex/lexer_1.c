/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:43:22 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 12:33:28 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v'
		|| c == '\f' || c == '\n')
		return (c);
	return (0);
}

int	ft_istoken(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == '(' || c == ')')
		return (c);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

void	ft_settoken(t_token *token, int type, char *s)
{
	token->type = type;
	token->text = s;
}

void	ft_gettext(t_token *token, char **strptr)
{
	char	*str;
	int		i;

	i = 0;
	while ((*strptr)[i] && !ft_isspace((*strptr)[i])
		&& !ft_istoken((*strptr)[i]) && !ft_isquote((*strptr)[i]))
	{
		i++;
	}
	str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(str, *strptr, i + 1);
	while (i)
	{
		(*strptr)++;
		i--;
	}
	ft_settoken(token, NOQUOTE, str);
}
