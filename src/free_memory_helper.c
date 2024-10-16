/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 05:27:00 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 17:23:51 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_header_ptr(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	del_header_list(t_list **header)
{
	t_list	*tmp;

	if (!header || !(*header))
	{
		printf("error:del_header_list");
		return ;
	}
	if (!((*header)->next))
	{
		if ((*header)->data)
			free((*header)->data);
		free_header_ptr((void **)header);
		return ;
	}
	tmp = (*header)->next;
	if ((*header)->data)
		free((*header)->data);
	free_header_ptr((void **)header);
	*header = tmp;
}

void	del_tokens(t_list **header)
{
	if (!header || !(*header))
	{
		printf("error:del_tokens");
		return ;
	}
	while (*header)
	{
		del_header_list(header);
	}
}

void	del_header_listd(t_listd **header)
{
	t_listd	*tmp;

	if (!header || !(*header))
	{
		printf("error:del_header_listd");
		return ;
	}
	if (!((*header)->next))
	{
		if ((*header)->data)
			free((*header)->data);
		free_header_ptr((void **)header);
		return ;
	}
	tmp = (*header)->next;
	tmp->prev = NULL;
	if ((*header)->data)
		free((*header)->data);
	free_header_ptr((void **)header);
	*header = tmp;
}
