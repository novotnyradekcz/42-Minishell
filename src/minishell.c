/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:30:12 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/20 14:48:37 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_memory(t_ms **ms, size_t size, char *message)
{
	*ms = malloc(size);
	if (!*ms)
	{
		printf("%s\n", message);
		return ;
	}
	ft_memset(*ms, '\0', size);
}

void	init_ms(t_ms *ms, char **env)
{
	env_to_listd(ms, env);
	ms->num_of_cmd = 1;
	ms->double_quotes = 0;
	ms->single_quotes = 0;
	ms->exit_status = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_ms	*ms;

	main_helper(argc, argv);
	allocate_memory(&ms, sizeof(t_ms), "Error: ms malloc");
	init_ms(ms, env);
	while (1)
	{
		ms->input = get_input(ms);
		if (check_input(ms))
			continue ;
		divide_input(ms);
		ex_commands(ms);
		free_one_input(ms);
	}
	free_all(ms);
	return (0);
}
