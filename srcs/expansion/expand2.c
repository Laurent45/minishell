/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:43:41 by rigel             #+#    #+#             */
/*   Updated: 2022/09/13 10:40:14 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	dollar_alloc2(char *tmp, char *new, char **tmp2)
{
	if (tmp == NULL)
		*tmp2 = ft_strjoin(new, "");
	else
		*tmp2 = ft_strjoin(new, tmp);
}
