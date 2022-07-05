/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:55:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 14:59:04 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include <stdlib.h>

int	ft_new_env(t_env **env, char *var, int globale)
{
	*env = (t_env *) malloc(sizeof(t_env));
	if (!(*env))
	{
		free(var);
		return (ft_allocated_err(0, "t_env * in ft_new_env"));
	}
	(*env)->var = var;
	(*env)->globale = globale;
	return (1);
}
