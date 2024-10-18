/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:25:24 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/18 14:16:38 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*strdup;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	strdup = (char *) malloc((i + 1) * sizeof(char));
	if (strdup == 0)
		return (0);
	while (i >= 0)
	{
		strdup[i] = str[i];
		i--;
	}
	return (strdup);
}
