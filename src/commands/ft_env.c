/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:41 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 15:20:57 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_args(char **arguments)
{
	if (arguments[0])
	{
		return (1);
	}
	return (0);
}

char	*env_str(char *env_key, char *env_value)
{
	char	*new_str;
	char	*tmp;
	char	*temp;

	tmp = ft_strjoin(env_key, "=");
	temp = ft_strjoin(tmp, env_value);
	new_str = ft_strjoin(temp, "\n");
	free(tmp);
	free(temp);
	return (new_str);
}

char	*all_env_str(t_listd *tmp, char *new_str_1)
{
	char	*temp_env_key;
	char	*temp_env_value;
	char	*temp_str;
	char	*new_str;

	temp_env_key = ((t_env *)tmp->data)->env_key;
	temp_env_value = ((t_env *)tmp->data)->env_value;
	temp_str = env_str(temp_env_key, temp_env_value);
	new_str = ft_strjoin(new_str_1, temp_str);
	free(temp_str);
	free(new_str_1);
	return (new_str);
}

void	ft_env(t_ms *ms)
{
	t_listd	*tmp;
	char	*new_str;
	int		original_fd;

	new_str = malloc(sizeof(char));
	new_str[0] = '\0';
	if (check_args(((t_cmd *)ms->commands->data)->arguments))
	{
		printf("run env without arguments\n");
		ms->exit_status = 127;
		return ;
	}
	tmp = ms->envar;
	while (tmp->next)
	{
		new_str = all_env_str(tmp, new_str);
		tmp = tmp->next;
	}
	new_str = all_env_str(tmp, new_str);
	original_fd = setup_fd(ms->commands->data);
	printf("%s", new_str);
	close_fd(ms->commands->data, original_fd);
	ms->exit_status = 0;
	free(new_str);
}
