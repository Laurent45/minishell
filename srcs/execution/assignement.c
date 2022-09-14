/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 21:55:33 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "env.h"

int	assignement(t_list **my_envp, t_list *var, int globale)
{
	while (var)
	{
		if (add_envvar(my_envp, (char *) var->content, globale) == FAILED)
			return (FAILED);
		var = var->next;
	}
	return (SUCCESS);
}
