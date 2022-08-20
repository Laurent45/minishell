/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:02:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/18 18:57:56 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

extern t_list	*g_envs;

static char	**ft_args_to_array(t_list *lst)
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

static int	ft_lstsize_globale(t_list *lst)
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

static char	**ft_envs_to_array(t_list *lst)
{
	t_env	*env;
	int		i;
	int		size;
	char	**ret;

	size = ft_lstsize_globale(lst);
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (lst)
	{
		env = (t_env *) lst->content;
		if (env->globale)
		{
			ret[i] = env->var;
			i++;
		}
		lst = lst->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	ft_run_executable(t_command *command)
{
	int		status;
	char	**args;
	char	**envp;

	status = ft_search_exe(command->cmd_args);
	if (status == 0)
	{
		args = ft_args_to_array(command->cmd_args);
		if (!args)
			return (1);
		envp = ft_envs_to_array(g_envs);
		if (!envp)
			return (free(args), 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(args[0], args, envp);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		free(args);
		free(envp);
		return (ft_perror(127, "execve"));
	}
	return (status);
}
