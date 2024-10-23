/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 05:28:42 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/23 17:58:56 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_line(char *line, char *eof, char *new_line)
{
	char	*temp;
	char	*tmp;

	temp = "";
	if (ft_strcmp(eof, line) != 0)
	{
		temp = ft_strjoin(line, "\n");
		if (!temp)
			return (NULL);
		tmp = ft_strjoin(new_line, temp);
		free(temp);
		if (!tmp)
			return (NULL);
		free(new_line);
		new_line = tmp;
	}
	return (new_line);
}

char	*get_input_heredoc(char *eof)
{
	char	*line;
	char	*prompt;
	char	*new_line;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char));
	if (!new_line)
		return (NULL);
	new_line[0] = '\0';
	line[0] = '\0';
	while (ft_strcmp(eof, line) != 0)
	{
		free(line);
		prompt = "heredoc>";
		line = readline(prompt);
		if (!line)
			return (0);
		new_line = get_new_line(line, eof, new_line);
	}
	free(line);
	return (new_line);
}

char	*get_input(t_ms *ms)
{
	char	*line;
	char	*prompt;

	prompt = "minishell>";
	line = readline(prompt);
	if (!line)
	{
		printf("exit\n");
		free_no_input(ms);
		exit(0);
	}
	if (line[0] != '\0')
	{
		add_history(line);
	}
	return (line);
}

void	close_fd(t_cmd *cmd, int original_stdout)
{
	if (cmd->redir)
	{
		if (ft_strcmp(cmd->redir, ">") == 0
			|| ft_strcmp(cmd->redir, ">>") == 0)
		{
			if (dup2(original_stdout, STDOUT_FILENO) < 0)
			{
				perror("dup2 restore stdout error");
				return ;
			}
		}
		else if (ft_strcmp(cmd->redir, "<") == 0
			|| ft_strcmp(cmd->redir, "<<") == 0)
		{
			if (dup2(original_stdout, STDIN_FILENO) < 0)
			{
				perror("dup2 restore stdout error");
				return ;
			}
		}
		close(original_stdout);
	}
	if (cmd->redir && ft_strcmp(cmd->redir, "<<") == 0)
		unlink("heredoc");
}

int	setup_fd(t_cmd *cmd)
{
	int	original_fd;

	original_fd = -1;
	if (cmd->redir)
	{
		if (ft_strcmp(cmd->redir, ">") == 0
			|| ft_strcmp(cmd->redir, ">>") == 0)
			original_fd = dup(STDOUT_FILENO);
		else if (ft_strcmp(cmd->redir, "<") == 0
			|| ft_strcmp(cmd->redir, "<<") == 0)
			original_fd = dup(STDIN_FILENO);
		handle_redir(cmd);
		return (original_fd);
	}
	return (-1);
}
