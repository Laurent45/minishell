/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:15:45 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/09 09:39:29 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_stdio.h"

int	ft_allocated_err(int ret, const char *type)
{
	perror(type);
	return (ret);
}

int	ft_puterror(int ret, char *message)
{
	ft_putstr_fd(message, 2);
	return (ret);
}
