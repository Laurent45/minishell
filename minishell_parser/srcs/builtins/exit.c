/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:36:17 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/17 11:24:32 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

int	ft_exit_built(t_list *args)
{
	(void) args;

	printf("You are in exit function\n");
	return (1);
}
