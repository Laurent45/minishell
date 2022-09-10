/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 18:06:43 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "expansion.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

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
