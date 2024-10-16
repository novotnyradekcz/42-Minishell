/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:23:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/16 16:31:38 by lmaresov         ###   ########.fr       */
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

	str = "";
	cmd = ms->commands->data;
	if (cmd->arguments[0])
		str = ft_echo_helper(((t_cmd *)ms->commands->data)->arguments);
	if (!cmd->option)
		str = ft_strjoin(str, "\n");
	if (cmd->redir)
		handle_redir(cmd, str);
	else
		printf("%s", str);
	ms->exit_status = 0;
}
