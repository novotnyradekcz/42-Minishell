/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:47:17 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/18 14:55:04 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_array_len(char **split)
{
	int	i;

	if (!split)
		return (-1);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	**ft_copy_array(char **arr)
{
	int		i;
	int		l;
	char	**newarr;

	i = 0;
	l = ft_array_len(arr) + 1;
	if (l < 0)
		return (NULL);
	newarr = malloc(sizeof(char *) * l);
	while (arr[i])
	{
		l = ft_strlen(arr[i]) + 1;
		newarr[i] = ft_calloc(sizeof(char), l);
		ft_strlcpy(newarr[i], arr[i], l);
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}

static int	ft_freeall(char **result, int k)
{
	while (k-- > 0)
		free(result[k]);
	free(result);
	return (1);
}

static int	ft_cpy(char **result, char const *s, char c, int size)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	k = 0;
	while (k < size)
	{
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		l = j;
		result[k] = (char *)malloc((l + 1) * sizeof(char));
		if (!result[k])
			return (ft_freeall(result, k));
		result[k][j] = '\0';
		while (j-- > 0)
			result[k][j] = s[i + j];
		i += l;
		k++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;
	int		i;

	if (!s)
		return (0);
	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			size++;
		i++;
	}
	result = (char **)malloc((size + 1) * sizeof(char *));
	if (!result)
		return (0);
	result[size] = 0;
	if (ft_cpy(result, s, c, size))
		return (0);
	return (result);
}
