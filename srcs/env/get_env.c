/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:00:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 22:04:48 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "init.h"

#include <stdlib.h>

char	*getenv_value(t_list *my_envp, char *varname)
{
	int		l_varname;
	int		l_currvar;
	char	*env_var;

	l_varname = ft_strlen(varname);
	if (ft_strcmp(varname, "?") == 0)
		return (ft_itoa(get_status()));
	while (my_envp)
	{
		env_var = (char *)((t_env *) my_envp->content)->varname;
		l_currvar = len_varname(env_var);
		if (l_currvar < l_varname)
			l_currvar = l_varname;
		if (ft_strncmp(env_var, varname, l_currvar) == 0)
			return (((t_env *) my_envp->content)->value);
		my_envp = my_envp->next;
	}
	return (NULL);
}

t_env	*get_env(t_list *my_envp, char *varname)
{
	int		l_varname;
	int		l_currvar;
	char	*env_var;

	l_varname = ft_strlen(varname);
	while (my_envp)
	{
		env_var = (char *)((t_env *) my_envp->content)->varname;
		l_currvar = len_varname(env_var);
		if (l_currvar < l_varname)
			l_currvar = l_varname;
		if (ft_strncmp(env_var, varname, l_currvar) == 0)
			return ((t_env *) my_envp->content);
		my_envp = my_envp->next;
	}
	return (NULL);
}
