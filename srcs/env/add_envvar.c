/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:01:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 15:57:45 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_string.h"

#include <stdlib.h>

static int	push_env(t_list **my_envp, char *envvar, int globale)
{
	t_env	*env;
	t_list	*node;

	if (new_env(&env, envvar, globale) == FAILED)
		return (FAILED);
	node = ft_lstnew((void *) new_env);
	if (!node)
		return (del_env(env), FAILED);
	ft_lstadd_back(my_envp, node);
	return (SUCCESS);
}

int	add_envvar(t_list **my_envp, char *envvar, int globale)
{
	t_env	*exist;
	char	*dup;
	char	*tmp;

	tmp = ft_substr(envvar, 0, strlenvar(envvar));
	if (!tmp)
		return (FAILED);
	exist = get_env(*my_envp, tmp);
	free(tmp);
	dup = ft_strdup(envvar);
	if (!dup)
		return (FAILED);
	if (exist)
	{
		if (ft_strchr(dup, '='))
		{
			free(exist->var);
			exist->var = dup;
		}
		else
			free(dup);
		exist->globale = globale;
		return (SUCCESS);
	}
	return (push_env(my_envp, dup, globale));
}
