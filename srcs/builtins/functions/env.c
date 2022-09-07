/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:00:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:29:30 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_stdio.h"
#include "error.h"

#include <unistd.h>

int	built_env(t_list *args, t_list **my_envp)
{
	t_env	*env;
	t_list	*tmp_envp;

	if (ft_lstsize(args) != 1)
		return (puterror(2, "env: options and arguments are not allow"));
	tmp_envp = *my_envp;
	while (tmp_envp)
	{
		env = (t_env *) tmp_envp->content;
		if (env->globale)
		{
			ft_putstr_fd(env->var, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp_envp = tmp_envp->next;
	}
	return (0);
}
