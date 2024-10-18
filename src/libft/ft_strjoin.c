/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:06:23 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/18 13:26:20 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strjoin_freeright(char const *s1, char *s2)
{
	size_t		len1;
	size_t		len2;
	size_t		i;
	char	*joined;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	joined = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (joined == 0)
		return (0);
	while (i < len1 + len2)
	{
		if (i < len1)
			joined[i] = s1[i];
		else
			joined[i] = s2[i - len1];
		i++;
	}
	joined[i] = '\0';
	free(s2);
	return (joined);
}

char	*ft_strjoin_freeleft(char *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	size_t		i;
	char	*joined;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	joined = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (joined == 0)
		return (0);
	while (i < len1 + len2)
	{
		if (i < len1)
			joined[i] = s1[i];
		else
			joined[i] = s2[i - len1];
		i++;
	}
	joined[i] = '\0';
	free(s1);
	return (joined);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	size_t		i;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	joined = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	while (i < len1 + len2)
	{
		if (i < len1)
			joined[i] = s1[i];
		else
			joined[i] = s2[i - len1];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}
