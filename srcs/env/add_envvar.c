/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:01:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 18:11:21 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_string.h"

#include <stdlib.h>
#include <stdio.h>

static int	push_env(t_list **my_envp, char *envvar, int globale)
{
	t_env	*env;
	t_list	*node;

	if (new_env(&env, envvar, globale) == FAILED)
		return (FAILED);
	node = ft_lstnew((void *) env);
	if (!node)
		return (del_env(env), FAILED);
	ft_lstadd_back(my_envp, node);
	return (SUCCESS);
}

static int	add_value(t_env *exist, char *value, int globale, char *equal_index)
{
	char	*n_value;

	if (equal_index[-1] == '+' && exist->value)
	{
			n_value = ft_strjoin(exist->value, value);
			free(value);
			if (!n_value)
				return (FAILED);
	}
	else
		n_value = value;
	free(exist->value);
	exist->value = n_value;
	if (exist->globale == 0)
		exist->globale = globale;
	return (SUCCESS);
}

int	add_envvar(t_list **my_envp, char *envvar, int globale)
{
	t_env	*exist;
	char	*equal_index;
	char	*tmp;

	tmp = ft_substr(envvar, 0, len_varname(envvar));
	if (!tmp)
		return (FAILED);
	exist = get_env(*my_envp, tmp);
	free(tmp);
	if (exist)
	{
		equal_index = ft_strchr(envvar, '=');
		if (equal_index)
		{
			tmp = ft_strdup(equal_index + 1);
			if (!tmp)
				return (FAILED);
			return (add_value(exist, tmp, globale, equal_index));
		}
		if (exist->globale == 0)	
			exist->globale = globale;
		return (SUCCESS);
	}
	return (push_env(my_envp, envvar, globale));
}
