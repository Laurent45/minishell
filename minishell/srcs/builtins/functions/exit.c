/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:36:17 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 17:03:44 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"

#include <stdio.h>

int	ft_exit_built(t_list *args)
{
	(void) args;
	if (ft_lstsize(args) > 1)
		return (ft_puterror(2, "options or arguments not allowed"));
	printf("exit \n");
	return (EXIT_BUILT);
}
