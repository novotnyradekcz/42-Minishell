/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:57:25 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/12 13:16:35 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void ft_cat(t_ms *ms)
{
    t_cmd * cmd;
    //char * str;

    cmd = ms->commands->data;
    //str = ft_echo_helper(((t_cmd *)ms->commands->data)->arguments);
    //handle_redirection_write(cmd, str);
    handle_redirection_read(cmd);
}