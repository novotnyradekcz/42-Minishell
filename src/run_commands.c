/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:11:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/23 18:30:18 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arguments_to_arg(char *command, char **arguments)
{
	char	**arg;
	int		i;

	i = 0;
	while (arguments[i])
		i++;
	arg = (char **)malloc(sizeof(char *) * (i + 2));
	if (!arg)
		return (NULL);
	arg[0] = ft_strdup(command);
	i = 0;
	while (arguments[i])
	{
		arg[i + 1] = ft_strdup(arguments[i]);
		i++;
	}
	arg[i + 1] = NULL;
	return (arg);
}

void	execute_other_helper(t_ms *ms, char **arg, char **env)
{
	handle_redir(((t_cmd *)ms->commands->data));
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, SIG_DFL);
	child_process(ms, env, arg);
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	execute_other(t_ms *ms)
{
	int		pid;
	char	**arg;
	char	**env;

	arg = arguments_to_arg(((t_cmd *)ms->commands->data)->command,
			((t_cmd *)ms->commands->data)->arguments);
	env = env_to_char(ms->envar);
	pid = fork();
	if (pid == 0)
		execute_other_helper(ms, arg, env);
	else if (pid < 0)
	{
		perror("fork failed");
		ms->exit_status = 1;
		ft_free_ae(arg, env);
		exit(1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &ms->exit_status, 0);
		signal(SIGINT, ft_handle_signal);
		unlink("heredoc");
		ft_free_ae(arg, env);
	}
}

void	run_commands(t_ms *ms)
{
	if (ms->num_of_cmd == 1)
	{
		if (check_builtin(ms))
			one_command(ms);
		else
			execute_other(ms);
	}
	else if (ms->num_of_cmd > 1)
	{
		run_pipe(ms);
	}
}
