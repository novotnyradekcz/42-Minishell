/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:23:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 18:17:30 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_echo_helper(char **arguments)
{
	char	*str;
	char	*str_2;
	char	*tmp_str;
	int		i;

	i = 0;
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (arguments[i + 1])
	{
		str_2 = ft_strdup(arguments[i]);
		tmp_str = ft_strjoin_with_space(str, str_2);
		free(str);
		free(str_2);
		str = tmp_str;
		i++;
	}
	str_2 = ft_strdup(arguments[i]);
	tmp_str = ft_strjoin(str, str_2);
	free(str);
	free(str_2);
	str = tmp_str;
	return (str);
}

char	*str_without_option(char *str)
{
	char	*str_tmp;
	
	str_tmp = str;
	str = ft_strjoin(str_tmp, "\n");
	free(str_tmp);
	return (str);
}

void	ft_echo(t_ms *ms)
{
	char	*str;
	t_cmd	*cmd;
	int		original_fd;
	

	str = malloc(sizeof(char));
	if (!str)
		return ;
	str[0] = '\0';
	cmd = ms->commands->data;
	if (cmd->arguments[0])
	{
		free(str);
		str = ft_echo_helper(((t_cmd *)ms->commands->data)->arguments);
	}
	if (!cmd->option || ft_strcmp(cmd->option, "-n") != 0)
	{
		str = str_without_option(str);
	}
	original_fd = setup_fd(cmd);
	printf("%s", str);
	close_fd(cmd, original_fd);
	ms->exit_status = 0;
	free(str);
}
