/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:05:39 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 22:24:20 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_redir(t_cmd *cmd)
{
	int		fd;
	char	*file_name;

	file_name = cmd->redir_file;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("error opening file");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("error dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	append_redir(t_cmd *cmd)
{
	int		fd;
	char	*file_name;

	file_name = cmd->redir_file;
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("error opening file");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("error dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	read_redir(t_cmd *cmd)
{
	int		fd;
	char	*file_name;

	file_name = cmd->redir_file;
	fd = open(file_name, O_RDWR);
	if (fd < 0)
	{
		perror("error opening file");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("error dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	heredoc_redir_helper(void)
{
	int		fd;

	fd = open("heredoc", O_RDONLY);
	if (fd < 0)
	{
		perror("error opening file");
		close(fd);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("error dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	heredoc_redir(t_cmd *cmd)
{
	char	*str;
	int		fd;

	str = get_input_heredoc(cmd->redir_file);
	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("error opening file");
		close(fd);
		return (1);
	}
	write(fd, str, ft_strlen(str));
	free(str);
	close(fd);
	if (heredoc_redir_helper())
		return (1);
	return (0);
}
