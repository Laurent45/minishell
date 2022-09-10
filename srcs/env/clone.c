/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:55:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 16:34:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_string.h"

#include <stdlib.h>

int	len_varname(char *varname)
{
	int	i;

	i = 0;
	while (varname[i] && varname[i] != '=')
	{
		if (varname[i] == '+' && varname[i + 1] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	new_env(t_env **env, char *env_var, int globale)
{
	char	*varname;
	char	*value;
	char	*equal_index;

	*env = (t_env *) malloc(sizeof(t_env));
	if (!(*env))
		return (puterror(FAILED, "t_env * in new_env"));
	varname = ft_substr(env_var, 0, len_varname(env_var));
	if (!varname)
		return (free(*env), FAILED);
	equal_index = ft_strchr(env_var, '=');
	if (equal_index == NULL)
		value = NULL;
	else
	{
		value = ft_strdup(equal_index + 1);
		if (!value)
			return (free(varname), free(*env), FAILED);
	}
	(*env)->varname = varname;
	(*env)->value = value;
	(*env)->globale = globale;
	return (SUCCESS);
}

int	clone_env(t_list **envs, char *envp[])
{
	t_list		*node_env;
	t_env		*env;
	int			i;

	*envs = NULL;
	i = 0;
	while (envp[i])
	{
		if (new_env(&env, envp[i], 1) == FAILED)
			return (clear_env(envs, FAILED));
		node_env = ft_lstnew((void *) env);
		if (!node_env)
			return (clear_env(envs, FAILED));
		ft_lstadd_back(envs, node_env);
		i++;
	}
	return (SUCCESS);
}
