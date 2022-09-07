/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:55:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 09:38:38 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"

#include <stddef.h>

t_built	*ft_isbuiltins(t_list *cmd_args, t_built *builts)
{
	int	i;

	if (cmd_args == NULL)
		return (NULL);
	i = 0;
	while (builts[i].func)
	{
		if (ft_strcmp(builts[i].func, (char *) cmd_args->content) == 0)
			return (&builts[i]);
		i++;
	}
	return (NULL);
}
