/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:28:49 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/19 12:29:01 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char ***arrptr)
{
	int		i;
	char	**arr;

	arr = *arrptr;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_mini_free(t_ms *ms)
{
	if (ms->lex)
		ft_lstclear(&ms->lex, ft_free_token);
	ms->lex = NULL;
	if (ms->exe)
		ft_lstclear(&ms->exe, ft_free_token);
	ms->exe = NULL;
	if (ms->csn)
		ft_free_cs(ms);
	ms->csn = 0;
}
