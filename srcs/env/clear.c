/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:10:10 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 15:04:42 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

#include <stdlib.h>

void	del_env(void *content)
{
	t_env	*env_var;

	env_var = (t_env *) content;
	free(env_var->varname);
	free(env_var->value);
	free(env_var);
}

int	clear_env(t_list **env, int ret)
{
	ft_lstclear(env, &del_env);
	return (ret);
}
