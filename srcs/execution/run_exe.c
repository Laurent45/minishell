/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:02:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/09 18:11:17 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "init.h"

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

extern int g_exit_status;

static char	**args_to_array(t_list *lst)
{
	int		size;
	int		i;
	char	**ret;

	size = ft_lstsize(lst);
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = (char *) lst->content;
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static int	lstsize_globale(t_list *lst)
{
	int		size;
	t_env	*env;

	size = 0;
	while (lst)
	{
		env = (t_env *) lst->content;
		if (env->globale)
			size++;
		lst = lst->next;
	}
	return (size);
}

static char	**envs_to_array(t_list *my_envp)
{
	t_env	*env;
	int		i;
	int		size;
	char	**ret;

	size = lstsize_globale(my_envp);
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (my_envp)
	{
		env = (t_env *) my_envp->content;
		if (env->globale)
		{
			ret[i] = env->var;
			i++;
		}
		my_envp = my_envp->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	run_executable(t_command *command, t_list **my_envp)
{
	char	**args;
	char	**envp;

	if (search_exe(command->cmd_args, *my_envp) == SUCCESS)
	{
		args = args_to_array(command->cmd_args);
		if (!args)
			return (1);
		envp = envs_to_array(*my_envp);
		if (!envp)
			return (free(args), 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(args[0], args, envp);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (errno == EACCES)
			set_status(126);
		else
			set_status(127);
		ft_perror(FAILED, args[0]);
		free(args);
		free(envp);
	}
	return (g_exit_status);
}
