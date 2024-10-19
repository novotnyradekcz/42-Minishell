/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:59:28 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 19:43:40 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_read(t_cmd *cmd)
{
	if (ft_strcmp(cmd->redir, "<") == 0)
	{
		read_redir(cmd);
	}
	if (ft_strcmp(cmd->redir, "<<") == 0)
	{
		heredoc_redir(cmd);
		return ;
	}
}

void	handle_redirection_write(t_cmd *cmd)
{
	if (ft_strcmp(cmd->redir, ">") == 0)
		write_redir(cmd);
	else if (ft_strcmp(cmd->redir, ">>") == 0)
		append_redir(cmd);
}

void	handle_redir(t_cmd *cmd)
{
	if (cmd->redir && (ft_strcmp(cmd->redir, ">") == 0
			|| ft_strcmp(cmd->redir, ">>") == 0))
	{
		handle_redirection_write(cmd);
	}
	else if (cmd->redir && (ft_strcmp(cmd->redir, "<") == 0
			|| ft_strcmp(cmd->redir, "<<") == 0))
	{
		handle_redirection_read(cmd);
	}
}
