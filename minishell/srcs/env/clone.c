/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:55:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/26 15:48:00 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_string.h"

#include <stdlib.h>

int	ft_new_env(t_env **env, char *var, int globale)
{
	*env = (t_env *) malloc(sizeof(t_env));
	if (!(*env))
	{
		free(var);
		return (ft_allocated_err(ENV_FAILED, "t_env * in ft_new_env"));
	}
	(*env)->var = var;
	(*env)->globale = globale;
	return (ENV_SUCCESS);
}

int	ft_clone_env(t_list **envs, char *envp[])
{
	t_list		*node_env;
	t_env		*env;
	char		*var;
	int			globale;
	int			i;

	*envs = NULL;
	i = 0;
	while (envp[i])
	{
		var = ft_strdup(envp[i]);
		if (!var)
			return (ft_clear_env(envs, ENV_FAILED));
		globale = 1;
		if (ft_new_env(&env, var, globale) == ENV_FAILED)
			return (ft_clear_env(envs, ENV_FAILED));
		node_env = ft_lstnew((void *) env);
		if (!node_env)
			return (ft_clear_env(envs, ENV_FAILED));
		ft_lstadd_back(envs, node_env);
		i++;
	}
	return (ENV_SUCCESS);
}
