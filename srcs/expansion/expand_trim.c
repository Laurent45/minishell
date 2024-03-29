/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:48:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/11 20:02:01 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

#include <stddef.h>

char	*expand_trim(char *value, t_list *my_envp)
{
	char	*str_expand;

	str_expand = expand(my_envp, value, 0, 0);
	if (!str_expand)
		return (NULL);
	str_expand = trim_quote(str_expand);
	if (!str_expand)
		return (NULL);
	return (str_expand);
}
