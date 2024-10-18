/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:00:43 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 20:12:23 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	main_helper(int argc, char **argv)
{
	if (argc != 1 || !argv)
	{
		printf("run program ./minishell without arguments\n");
		exit(1);
	}
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	check_input(t_ms *ms)
{
	if (ft_strcmp(ms->input, "") == 0
		|| only_whitespace(ms->input))
		return (1);
	if (syntax_error(ms))
		return (1);
	return (0);
}

void	free_one_input(t_ms *ms)
{
	free_ms_input(ms);
	free_ms_tokens(ms);
	free_ms_commands(ms);
}

void	ex_commands(t_ms *ms)
{
	if (ft_strcmp(((t_cmd *)ms->commands->data)->command, "echo") == 0
		&& ((t_cmd *)ms->commands->data)->arguments[0]
		&& ft_strcmp(((t_cmd *)ms->commands->data)->arguments[0], "$?") == 0)
	{
		printf("%d\n", ms->exit_status);
		ms->exit_status = 0;
	}
	else
		run_commands(ms);
}