/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaresov <lmaresov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:11:11 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/18 20:27:03 by lmaresov         ###   ########.fr       */
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
	
	//printf("execute other\n");
	arg = arguments_to_arg(((t_cmd *)ms->commands->data)->command, 
		((t_cmd *)ms->commands->data)->arguments);
	env = env_to_char(ms->envar);
	// while (*arg)
	// {
	// 	printf("arg: %s\n", *arg);
	// 	arg++;
	// }
	// while (*env)
	// {
	// 	printf("env: %s\n", *env);
	// 	env++;
	// }
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

void run_commands(t_ms *ms)
{
    if (ms->num_of_cmd == 1)
    {
        if (check_builtin(ms))
			one_command(ms);
		else
			execute_other(ms);
	}
    /*else if (ms->num_of_cmd > 1)
    {
        more_commands(ms);
    }*/
}