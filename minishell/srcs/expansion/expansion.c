/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:48:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/23 23:06:26 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "ft_string.h"

#include <stddef.h>

char	*ft_expand_trim(char *value)
{
	char	*expand;

	if (ft_strchr(value, '\''))
		expand = ft_expand(value, 2, 0);
	else
		expand = ft_expand(value, 1, 0);
	if (!expand)
		return (NULL);
	expand = ft_trim_quote(expand);
	if (!expand)
		return (NULL);
	return (expand);
}
