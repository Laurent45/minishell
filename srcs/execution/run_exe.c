/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:02:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 18:21:34 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "init.h"
#include "ft_string.h"

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

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

static int	nb_envvar(t_list *lst)
{
	int		size;
	t_env	*env;

	size = 0;
	while (lst)
	{
		env = (t_env *) lst->content;
		if (env->globale && env->value)
			size++;
		lst = lst->next;
	}
	return (size);
}

static char	*concat_name_value(t_env *envvar)
{
	char	*tmp;
	char	*name_value;
	char	*shlvl;

	tmp = ft_strjoin(envvar->varname, "=");
	if (!tmp)
		return (NULL);
	if (ft_strcmp(envvar->varname, "SHLVL") == 0)
	{
		shlvl = ft_itoa(ft_atoi(envvar->value) + 1);
		if (!shlvl)
		{
			free(tmp);
			return (NULL);
		}
		name_value = ft_strjoin(tmp, shlvl);
		free(tmp);
		return (name_value);
	}
	name_value = ft_strjoin(tmp, envvar->value);
	free(tmp);
	return (name_value);
}

static char	**envs_to_array(t_list *my_envp)
{
	t_env	*env;
	int		i;
	char	**ret;

	ret = (char **) malloc(sizeof(char *) * (nb_envvar(my_envp) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (my_envp)
	{
		env = (t_env *) my_envp->content;
		if (env->globale && env->value)
		{
			ret[i] = concat_name_value(env);
			if (ret[i] == NULL)
			{
				ft_clear_split(ret);
				return (NULL);
			}
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
		ft_clear_split(envp);
	}
	return (get_status());
}
