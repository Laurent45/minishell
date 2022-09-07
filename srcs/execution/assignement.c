/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:54:59 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "expansion.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

extern t_list	*g_envs;

int	assignement(t_list **my_envp, t_list *var, int globale)
{
	int		equal;
	char	*value_expand;
	char	*varname;
	char	*name_value;

	while (var)
	{
		equal = ft_strchr((char *) var->content, '=') - (char *) var->content;
		value_expand = expand_trim((char *) var->content + equal + 1, *my_envp);
		if (!value_expand)
			return (puterror(FAILED, "assignement failed"));
		varname = ft_substr((char *) var->content, 0, equal + 1);
		if (!varname)
			return (free(value_expand), puterror(FAILED, "assignement failed"));
		name_value = ft_strjoin(varname, value_expand);
		free(value_expand);
		free(varname);
		if (!name_value)
			return (puterror(FAILED, "assignement failed"));
		if (add_envvar(my_envp, name_value, globale) == FAILED)
			return (free(name_value), puterror(FAILED, "assignement failed"));
		free(name_value);
		var = var->next;
	}
	return (SUCCESS);
}
