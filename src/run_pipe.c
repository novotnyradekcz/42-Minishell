/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:08:47 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 17:22:21 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(char *str, t_ms *ms)
{
	perror(str);
	ms->exit_status = 1;
	return ;
}

void	child_process_pipes(t_ms *ms, int prev_fd_read, int *pipefd, int first)
{
	if (!first)
	{
		dup2(prev_fd_read, STDIN_FILENO);
		close(prev_fd_read);
	}
	if (ms->commands->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (check_builtin(ms))
		one_command(ms);
	else
		execute_other(ms);
	exit(0);
}

void	run_pipe(t_ms *ms)
{
	int	pipefd[2];
	int	prev_fd_read;
	int	first;
	int	pid;

	first = 1;
	prev_fd_read = -1;
	while (ms->commands)
	{
		if (ms->commands->next)
			if (pipe(pipefd) == -1)
				perror_exit("Error: pipe failed", ms);
		pid = fork();
		if (pid < 0)
			perror_exit("Error: fork failed", ms);
		if (pid == 0)
			child_process_pipes(ms, prev_fd_read, pipefd, first);
		wait(&ms->exit_status);
		if (!first)
			close(prev_fd_read);
		prev_fd_read = pipefd[0];
		close(pipefd[1]);
		ms->commands = ms->commands->next;
		first = 0;
	}
}
