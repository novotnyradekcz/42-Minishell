/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:23:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 16:51:36 by lmaresov         ###   ########.fr       */
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

void	ft_echo(t_ms *ms)
{
	char	*str;
	t_cmd	*cmd;
	int		original_fd;

	str = "";
	cmd = ms->commands->data;
	if (cmd->arguments[0])
		str = ft_echo_helper(((t_cmd *)ms->commands->data)->arguments);
	if (!cmd->option || ft_strcmp(cmd->option, "-n") != 0)
		str = ft_strjoin(str, "\n");
	original_fd = setup_fd(cmd);
	printf("%s", str);
	close_fd(cmd, original_fd);
	ms->exit_status = 0;
}
