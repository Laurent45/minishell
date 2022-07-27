/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:01:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 11:09:38 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"

#include <stdlib.h>

extern t_list	*g_envs;

static int	ft_push_env(char *envvar, int globale)
{
	t_env	*new_env;
	t_list	*node;

	if (ft_new_env(&new_env, envvar, globale) == ENV_FAILED)
		return (0);
	node = ft_lstnew((void *) new_env);
	if (!node)
		return (ft_del_env(new_env), 0);
	ft_lstadd_back(&g_envs, node);
	return (1);
}

int	ft_add_envvar(char *envvar, int globale)
{
	t_env	*exist;
	char	*dup;
	char	*tmp;

	tmp = ft_substr(envvar, 0, ft_strlenvar(envvar));
	if (!tmp)
		return (0);
	exist = ft_getenv(tmp);
	free(tmp);
	dup = ft_strdup(envvar);
	if (!dup)
		return (0);
	if (exist)
	{
		if (ft_strchr(dup, '='))
		{
			free(exist->var);
			exist->var = dup;
		}
		if (globale)
			exist->globale = globale;
		return (1);
	}
	return (ft_push_env(dup, globale));
}
