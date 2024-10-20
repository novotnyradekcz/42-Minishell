/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 06:33:33 by lmaresov          #+#    #+#             */
/*   Updated: 2024/10/19 10:44:34 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cdnew(t_ms *ms, char *argv[])
{
	char	cwd[4096];
	int		r;
	char	*t;
	char	*err;

	t = getcwd(cwd, 4096);
	r = chdir(argv[1]);
	if (r < 0)
	{
		r = errno;
		err = ft_strjoin("minishell: cd: ", argv[1]);
		ft_werror(err, NULL, NULL);
		free(err);
	}
	else
	{
		ft_changeenvval(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvval(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
	}
	return (r);
}

static void	ft_update_cdold(t_ms *ms, char *t, char *cwd)
{
	ft_changeenvval(ms, "OLDPWD", t);
	t = getcwd(cwd, 4096);
	ft_changeenvval(ms, "PWD", t);
	free(ms->prompt);
	ft_init_prompt(ms);
	printf("%s\n", t);
}

static int	ft_cdold(t_ms *ms)
{
	char	cwd[4096];
	int		r;
	char	*o;
	char	*t;

	t = getcwd(cwd, 4096);
	o = ft_getenvval(ms, "OLDPWD");
	if (!o)
	{
		r = 1;
		ft_werror("minishell: cd: OLDPWD not set\n", NULL, NULL);
		return (r);
	}
	r = chdir(o);
	if (r < 0)
	{
		r = errno;
		ft_werror("cd", NULL, NULL);
	}
	else
		ft_update_cdold(ms, t, cwd);
	return (r);
}

static int	ft_cdhome(t_ms *ms)
{
	char	cwd[4096];
	int		r;
	char	*h;
	char	*t;

	t = getcwd(cwd, 4096);
	h = ft_getenvval(ms, "HOME");
	r = chdir(h);
	if (r < 0)
	{
		r = errno;
		ft_werror("cd", NULL, NULL);
	}
	else
	{
		ft_changeenvval(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvval(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
	}
	return (r);
}

void	ft_cd(t_ms *ms, char *argv[])
{
	int	r;

	r = 0;
	if (!argv[1] || (argv[1][0] == '-' && argv[1][1] == '-' && !argv[1][2]))
		ft_cdhome(ms);
	else if (argv[2])
	{
		perror("minishell: cd: too many arguments\n");
		r = 1;
	}
	else if (argv[1][0] == '-' && !argv[1][1])
		r = ft_cdold(ms);
	else
		r = ft_cdnew(ms, argv);
	ms->err[0] = r;
	ms->error = r;
	ms->err[1] = 1;
}
