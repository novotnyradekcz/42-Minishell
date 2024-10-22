/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:00:43 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/22 21:53:20 by rnovotny         ###   ########.fr       */
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

void	free_token_node(t_list *tokens)
{
	if (tokens->data)
	{
		free(tokens->data);
		tokens->data = NULL;
	}
	free(tokens);
}
