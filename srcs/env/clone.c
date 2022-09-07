/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:55:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:16:45 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_string.h"

#include <stdlib.h>

int	new_env(t_env **env, char *var, int globale)
{
	*env = (t_env *) malloc(sizeof(t_env));
	if (!(*env))
	{
		free(var);
		return (puterror(FAILED, "t_env * in new_env"));
	}
	(*env)->var = var;
	(*env)->globale = globale;
	return (SUCCESS);
}

int	clone_env(t_list **envs, char *envp[])
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
			return (clear_env(envs, FAILED));
		globale = 1;
		if (new_env(&env, var, globale) == FAILED)
			return (clear_env(envs, FAILED));
		node_env = ft_lstnew((void *) env);
		if (!node_env)
			return (clear_env(envs, FAILED));
		ft_lstadd_back(envs, node_env);
		i++;
	}
	return (SUCCESS);
}
