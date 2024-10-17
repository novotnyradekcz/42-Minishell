/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:11:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/17 20:43:17 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_command(char *command)
{
    if(strcmp(command, "echo") == 0)
      return (1);
    else if (strcmp(command, "cd") == 0)
        return (2);
    else if (strcmp(command, "pwd") == 0)
        return (3);
    else if (strcmp(command, "export") == 0)
        return (4);
    else if (strcmp(command, "unset") == 0)
        return (5);
    else if (strcmp(command, "env") == 0)
        return (6);
    else if (strcmp(command, "exit") == 0)
        return (7);
    else
        return (0);
}


int one_command(t_ms *ms)
{
    if (!ms->commands->data)
    {
       //printf("CHyba 2\n");
       return (0);
    }    
    if (!check_command(((t_cmd *)ms->commands->data)->command))
    {
        printf ("This command is not in options\n");
        return (0);
    }
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 1)
    {
        ft_echo(ms);
    } 
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 2)
        ft_cd(ms);
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 3)
        ft_pwd(ms);
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 4)
        ft_export(ms);
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 5)
        ft_unset(ms);
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 6)
        ft_env(ms);
    else if (check_command(((t_cmd *)ms->commands->data)->command) == 7)
        ft_exit(ms);
    return (1);   
}




char **env_to_char(t_listd *envar)
{
	t_listd *cur_node;
	char **env;
	int i;
	
	cur_node = envar;
	i = 0;
	while (cur_node)
	{
		i++;
		cur_node = cur_node->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	cur_node = envar;
	while (cur_node)
	{
		env[i] = ft_strdup(((t_env *)cur_node->data)->env_key);
		env[i] = ft_strjoin_freeleft(env[i], "=");
		env[i] = ft_strjoin_freeleft(env[i], ((t_env *)cur_node->data)->env_value);
		i++;
		cur_node = cur_node->next;
	}
	env[i] = NULL;
	return (env);
}

int	check_exec_or_dir(char *path)
{
	//printf("check_exec_or_dir\n");
	if (ft_strchr(path, '/') != NULL && (path[0] == '/' || path[0] == '.'))
		{
			//printf("true\n"); 
			return (1);
			}
	else
		{
			//printf("false\n"); 
			return (0);
		}
		
}

char *get_path(char **path_array, char *command)
{
	int i;
	char *path;
	
	i = 0;
	while (path_array[i])
	{
		path = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(path, command);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	child_process(t_ms *ms, char **env, char **arg)
{
	char	*path;
	char	**path_array;

	//printf("child process\n");
	if (check_exec_or_dir(arg[0]))
	{
		//printf("error");
		path = ft_strdup(arg[0]);
		//printf("path 0: %s\n", path);
	}
	else
	{
		//printf("chyba");
		path_array = ft_split(env_value(ms->envar, "PATH"), ':');
		//printf("path_array: %s\n", path_array[0]);
		path = get_path(path_array, arg[0]);
		//printf("path 2: %s\n", path);
	}
	//printf("chyba2");
	if (!path)
	{
		ms->exit_status = 127;
		//printf("minishell: %s: command not found\n", arg[0]);
		exit(127);
	}
	execve(path, arg, env);
}


char **arguments_to_arg(char *command, char **arguments)
{
	char **arg;
	int i;
	
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
	{
		handle_redir(((t_cmd *)ms->commands->data));
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(ms, env, arg);
	}
	else if (pid < 0)
	{
		printf("Error: fork failed\n");
		ms->exit_status = 1;
		exit(1);
	}
	else
	{
		waitpid(pid, &ms->exit_status, 0);
		unlink("heredoc");
	}
}
/*
void	run_pipe(t_ms *ms)
{
	int		pid;
	int		pipefd[2];
	int		first;
	t_list	*cmd;

	first = 1;
	cmd = ms->commands;
	while (cmd)
	{
		if (!(cmd->next))
		{
			pipe(pipefd);
		}
		pid = fork();
		if (pid == 0)
		{
			if (!first)
			{
				dup2(((t_cmd *)cmd->data)->in_fd, STDIN_FILENO);
				close(((t_cmd *)cmd->data)->in_fd);
				close(((t_cmd *)cmd->data)->out_fd);
			}
			if (cmd->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				close(pipefd[0]);
			}
			if (check_builtin(ms))
				one_command(ms);
			else
				execute_other(ms);
			exit(0);
		}
		else if (pid < 0)
		{
			printf("Error: fork failed\n");
			ms->exit_status = 1;
			exit(1);
		}
		else
		{
			printf("run_pipe: parent\n");
			if (!first)
			{
				close(((t_cmd *)cmd->data)->in_fd);
				close(((t_cmd *)cmd->data)->out_fd);
			}
			if (cmd->next)
			{
				close(pipefd[1]);
				((t_cmd *)cmd->next->data)->in_fd = pipefd[0];
				((t_cmd *)cmd->data)->out_fd = pipefd[1];
			}
			cmd = cmd->next;
			first = 0;
			// waitpid(pid, &ms->exit_status, 0);
		}
	}
	waitpid(pid, &ms->exit_status, 0);
	// while(wait(NULL) > 0);
}
*/

void	run_pipe(t_ms *ms)
{
	int		prev_pipe[2];
	int		curr_pipe[2];
	t_list	*cmd;
	int		first;
	int		pid;
	// int		original_fd;

	cmd = ms->commands;
	// if (((t_cmd *)cmd->data)->redir)
	// {
	// 	printf("redir: %s\n", ((t_cmd *)cmd->data)->redir);
	// 	if (ft_strcmp(((t_cmd *)cmd->data)->redir, ">") == 0 || ft_strcmp(((t_cmd *)cmd->data)->redir, ">>") == 0 )
	// 		original_fd = dup(STDOUT_FILENO);
	// 	else if (ft_strcmp(((t_cmd *)cmd->data)->redir, "<") == 0 || ft_strcmp(((t_cmd *)cmd->data)->redir, "<<") == 0)
	// 		original_fd = dup(STDIN_FILENO);
	// }
	printf("run_pipe: %s\n", ((t_cmd *)cmd->data)->command);
	printf("run_pipe: %s\n", ((t_cmd *)cmd->data)->redir_file);
	
	printf("run_pipe: %s\n", ((t_cmd *)cmd->next->data)->command);
	printf("run_pipe: %s\n", ((t_cmd *)cmd->next->data)->redir_file);

	printf("run_pipe: %s\n", ((t_cmd *)cmd->next->next->data)->command);
	printf("run_pipe: %s\n", ((t_cmd *)cmd->next->next->data)->redir_file);

	printf("run_pipe: %s\n", ((t_cmd *)cmd->next->next->next->data)->command);
	printf("run_pipe: %s\n", ((t_cmd *)cmd->next->next->next->data)->redir_file);
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(curr_pipe) == -1)
			{
				perror("Error: pipe failed\n");
				ms->exit_status = 1;
				exit(1);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Error: fork failed\n");
			ms->exit_status = 1;
			exit(1);
		}
		if (pid == 0)
		{
			if (!first)
			{
				dup2(prev_pipe[0], STDIN_FILENO);
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (cmd->next)
			{
				close(curr_pipe[0]);
				dup2(curr_pipe[1], STDOUT_FILENO);
				close(curr_pipe[1]);
			}
			if (check_builtin(ms))
				one_command(ms);
			else
				execute_other(ms);
			// if (((t_cmd *)cmd->data)->redir)
			// 	close_fd(((t_cmd *)cmd->data), original_fd);
			exit(0);
		}
		if (!first)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
		cmd = cmd->next;
		first = 0;
	}
	// close(curr_pipe[0]);
	// close(curr_pipe[1]);
	while (wait(NULL) > 0);
	
}

void run_commands(t_ms *ms)
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
        // printf("run_commands\n");
		run_pipe(ms);
		printf("exit_status: %d\n", ms->exit_status);
    }
}