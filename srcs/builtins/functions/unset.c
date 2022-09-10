/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:38:15 by llepiney          #+#    #+#             */
/*   Updated: 2022/09/10 17:17:58 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "error.h"
#include "init.h"

#include <stdio.h>
#include <stdlib.h>

void	delenvvar(t_list **my_envp, char *varname)
{
	t_list	*before;
	t_list	*tmp_envp;
	int		l_varname;
	int		len_currvar;

	before = NULL;
	tmp_envp = *my_envp;
	l_varname = ft_strlen(varname);
	while (tmp_envp)
	{
		len_currvar = len_varname((char *)((t_env *) tmp_envp->content)->varname);
		if (len_currvar < l_varname)
			len_currvar = l_varname;
		if (ft_strncmp((char *)((t_env *) tmp_envp->content)->varname, \
					varname, len_currvar) == 0)
		{
			if (before == NULL)
				*my_envp = tmp_envp->next;
			else
				before->next = tmp_envp->next;
			return (del_env((void *) tmp_envp->content), free(tmp_envp));
		}
		before = tmp_envp;
		tmp_envp = tmp_envp->next;
	}
}

int	built_unset(t_list *args, t_list **my_envp)
{
	char	*varname;
	int		ret;

	if (ft_lstsize(args) == 1)
		return (set_status(0), SUCCESS);
	ret = 0;
	while (args)
	{
		varname = (char *) args->content;
		if ((varname[0] != '_' && ft_isalpha(varname[0]) == 0) \
				|| ft_strchr(varname, '='))
			ret = puterror(1, "unset: not a valid identifier");
		else
			delenvvar(my_envp, varname);
		args = args->next;
	}
	set_status(ret);
	return (SUCCESS);
}
