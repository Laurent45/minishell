/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:38:15 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/27 17:01:29 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

extern t_list	*g_envs;

void	ft_delenvvar(char *varname)
{
	t_list	*envs;
	t_list	*before;
	int		len_varname;
	int		len_currvar;

	envs = g_envs;
	before = NULL;
	len_varname = ft_strlen(varname);
	while (envs)
	{
		len_currvar = ft_strlenvar((char *)((t_env *) envs->content)->var);
		if (len_currvar < len_varname)
			len_currvar = len_varname;
		if (ft_strncmp((char *)((t_env *) envs->content)->var, \
					varname, len_currvar) == 0)
		{
			if (before == NULL)
				g_envs = envs->next;
			else
				before->next = envs->next;
			return (ft_del_env((void *) envs->content), free(envs));
		}
		before = envs;
		envs = envs->next;
	}
}

int	ft_unset(t_list *args)
{
	char	*varname;
	int		ret;

	if (ft_lstsize(args) == 1)
		return (0);
	ret = 0;
	while (args)
	{
		varname = (char *) args->content;
		if ((varname[0] != '_' && ft_isalpha(varname[0]) == 0) \
				|| ft_strchr(varname, '='))
			ret = ft_puterror(1, "unset: not a valid identifier");
		else
			ft_delenvvar(varname);
		args = args->next;
	}
	return (ret);
}
