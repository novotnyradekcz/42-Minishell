/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:41:19 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 17:47:51 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*pmemory;

	i = 0;
	pmemory = (char *)s;
	while (i < n)
	{
		pmemory[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
