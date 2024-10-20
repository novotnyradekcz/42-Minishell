/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:54:27 by rnovotny          #+#    #+#             */
/*   Updated: 2024/10/19 12:23:08 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_warning(t_ms *ms, int i, int j)
{
	char	*delimiter;

	delimiter = ms->cs[i].ct[j].hd;
	write(2, "\nminishell: warning: here-document ", 35);
	write(2, "delimited by end-of-file (wanted'", 33);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
	ft_exit(NULL, 1);
}

static void	ft_exit_helper(t_ms *ms, char *line, int i, int pid)
{
	if (pid < 0)
	{
		ft_exit(NULL, 1);
	}
	else if (line)
	{
		free(line);
		ft_closefds(ms, i);
		ft_closepipes(ms, i);
		ft_exit(NULL, 1);
	}
}

static void	ft_error_creating_pipe(void)
{
	write(2, "Error with creating pipe\n", 25);
	ft_exit(NULL, 1);
}

static void	ft_while_loop_end(t_ms *ms, int i, int j, char *line)
{
	write(ms->cs[i].ct[j].hdpipe[1], line, ft_strlen(line));
	free(line);
}

void	ft_forking_helper(t_ms *ms, int i, int j)
{
	char	*line;
	int		pid;

	line = NULL;
	if (pipe(ms->cs[i].ct[j].hdpipe) == -1)
		ft_error_creating_pipe();
	pid = fork();
	ft_exit_helper(ms, line, i, pid);
	if (pid == 0)
	{
		signal(SIGINT, ft_newglobal_sig);
		while (1)
		{
			// write (1, "> ", 2);
			// line = get_next_line(0);
			line = readline("> ");
			if (line == NULL)
				ft_warning(ms, i, j);
			if (ft_strncmp(line, ms->cs[i].ct[j].hd,
					ft_strlen(ms->cs[i].ct[j].hd)) == 0)
				break ;
			ft_while_loop_end(ms, i, j, line);
		}
		ft_exit_helper(ms, line, i, pid);
	}
	ft_wait(ms, pid, 0);
}
