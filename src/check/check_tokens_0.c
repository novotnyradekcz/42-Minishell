/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:57:55 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 18:56:20 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_parentheses_helper(t_check *check)
{
	if (check->token->type & OPENPAR)
	{
		if (!check->text)
		{
			check->parentheses++;
			if (!check->stuff)
			{
				check->stuff = 1;
				check->status = 1;
			}
		}
		else
			check->status = 3;
	}
}

void	ft_check_parentheses(t_check *check)
{
	ft_check_parentheses_helper(check);
	if (check->token->type & CLOSEPAR && check->text)
	{
		if (check->text)
		{
			check->parentheses--;
			if (!check->stuff)
			{
				check->stuff = 1;
				check->status = 1;
			}
		}
		else
			check->status = 3;
	}
	if (check->parentheses < 0)
		check->status = 3;
}

static void	ft_tokenchecker_helper(t_ms *ms, t_list	*lst, t_check *check)
{
	if (!check->status)
		ft_extra_check(lst, check);
	if (check->status)
	{
		ms->error = 2;
		ms->csn = 0;
		perror("minishell: syntax error, unexpected token\n");
	}
}

static void	ft_tokenchecker_helper2(t_list *lst, t_check *check)
{
	check->token = lst->content;
	ft_check_text(check);
	ft_check_parentheses(check);
	ft_check_stuff(check);
}

int	ft_tokenchecker(t_ms *ms)
{
	t_list	*lst;
	t_check	check_origin;
	t_check	*check;

	check = &check_origin;
	check->text = 0;
	check->parentheses = 0;
	check->stuff = 0;
	check->status = 0;
	lst = ms->lex;
	while (lst)
	{
		ft_tokenchecker_helper2(lst, check);
		if (check->status > 2)
			break ;
		lst = lst->next;
	}
	if (!check->stuff)
		return (1);
	if (check->parentheses)
		check->status = 3;
	lst = ms->lex;
	ft_tokenchecker_helper(ms, lst, check);
	return (check->status);
}
