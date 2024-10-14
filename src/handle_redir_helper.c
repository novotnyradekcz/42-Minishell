/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:05:39 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/13 12:11:30 by lmaresov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int write_redir(t_cmd *cmd, char * str)
{
    int fd;
    char * file_name;
    ssize_t bytes_written;

    file_name = cmd->redir_file;
    fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf ("error opening file\n");
        return 1;
    }
    bytes_written = write(fd, str, ft_strlen(str));
    if (bytes_written == -1)
    {
        printf( "error in writing to file\n");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

int append_redir(t_cmd *cmd, char * str)
{
    int fd;
    char * file_name;
    ssize_t bytes_written;

    file_name = cmd->redir_file;
    fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        printf ("error opening file\n");
        return 1;
    }
    bytes_written = write(fd, str, ft_strlen(str));
    if (bytes_written == -1)
    {
        printf( "error in writing to file\n");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

char *read_redir(t_cmd * cmd)
{
    int fd;
    char * file_name;
    ssize_t bytes_read;
    char *result;
    char *tmp;
    char buffer[1024];
    
    bytes_read = 0;
    result = malloc(sizeof(char));
    result[0] = '\0';
    file_name = cmd->redir_file;
    fd = open(file_name, O_RDWR);
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        tmp = ft_strjoin(result,(char*)buffer);
        free(result);
        result = tmp;
        ft_memset(buffer, '\0', sizeof(buffer));
    }
    return (result);
}

char * heredoc_redir(t_cmd * cmd)
{
    char * str;

    //printf("cmd: %s , eof: %s\n", cmd->command, cmd->redir_file);
    str = get_input_heredoc(cmd->redir_file);
    //printf("%s", str);
    return (str);
}
