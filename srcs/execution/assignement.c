/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/30 09:46:21 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "expansion.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

extern t_list	*g_envs;

int	ft_assignement(t_list *var, int globale)
{
	int		equal;
	char	*value_expand;
	char	*varname;
	char	*varname_value;

	while (var)
	{
		equal = ft_strchr((char *) var->content, '=') - (char *) var->content;
		value_expand = ft_expand_trim((char *) var->content + equal + 1);
		if (!value_expand)
			return (ft_puterror(0, "assignement failed"));
		varname = ft_substr((char *) var->content, 0, equal + 1);
		if (!varname)
			return (free(value_expand), ft_puterror(0, "assignement failed"));
		varname_value = ft_strjoin(varname, value_expand);
		free(value_expand);
		free(varname);
		if (!varname_value)
			return (ft_puterror(0, "assignement failed"));
		if (ft_add_envvar(varname_value, globale) == 0)
			return (free(varname_value), ft_puterror(0, "assignement failed"));
		free(varname_value);
		var = var->next;
	}
	return (1);
}
