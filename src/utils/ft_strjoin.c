/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:40:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 13:51:01 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len12;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len12 = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof (char) * len12 + 1);
	if (!new_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin_freeleft(char *s1, char *s2)
{
	char	*new_str;
	int		len12;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len12 = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof (char) * len12 + 1);
	if (!new_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_strjoin_with_space(char const *s1, char const *s2)
{
	char	*new_str;
	int		len12;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len12 = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof (char) * len12 + 1 + 1);
	if (!new_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = ' ';
	new_str[i + 1] = '\0';
	return (new_str);
}
