/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:51:45 by lmaresov          #+#    #+#             */
/*   Updated: 2024/09/21 10:49:56 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s) || !s || len <= 0)
	{
		substr = (char *)malloc(sizeof(char) * (len + 1));
		if (!substr)
			return (NULL);
		substr[i] = '\0';
		return (substr);
	}
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while(s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	if (!ft_isascii(c))
		return ((char *)s);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	else
		return (0);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

int is_whitespace(int c)
{
    if (c == 32 || (c >= 9 && c <= 13))
    {
        return (1);
    }
    return (0);
}

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
	new_str[i+1] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		s_len;
	int		i;

	i = 0;
	s_len = ft_strlen(s);
	new_str = (char *)malloc(sizeof (*new_str) * (s_len + 1));
	if (!new_str)
		return (NULL);
	while (s[i] != '\0')
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}