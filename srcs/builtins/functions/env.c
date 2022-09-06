/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:00:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 17:00:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_stdio.h"
#include "error.h"

#include <unistd.h>

extern t_list	*g_envs;

int	ft_env(t_list *args)
{
	t_list	*envs;
	t_env	*env;

	if (ft_lstsize(args) != 1)
		return (ft_puterror(2, "env: options and arguments are not allow"));
	envs = g_envs;
	while (envs)
	{
		env = (t_env *) envs->content;
		if (env->globale)
		{
			ft_putstr_fd(env->var, 1);
			ft_putstr_fd("\n", 1);
		}
		envs = envs->next;
	}
	return (0);
}
