/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 08:03:44 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/26 09:53:40 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	ft_copy_old(char **oldarr, char **newarr, int l, int n)
{
	int	i;

	i = 0;
	while (oldarr[i] && i < n)
	{
		newarr[i] = oldarr[i];
		i++;
	}
	while (i < l)
	{
		newarr[i + 1] = oldarr[i];
		i++;
	}
}

static char	*ft_insert_new(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

int	ft_array_insert(char ***array, char *str, int n)
{
	int		l;
	char	**oldarr;
	char	**newarr;

	if (!array || !*array || !str)
		return (-1);
	oldarr = *array;
	l = ft_array_len(oldarr) + 1;
	newarr = malloc(sizeof(char *) * (l + 1));
	if (!newarr || l <= n)
		return (-1);
	ft_copy_old(oldarr, newarr, l, n);
	newarr[n] = ft_insert_new(str);
	*array = newarr;
	free(oldarr);
	return (0);
}
