/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:00:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 21:10:50 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"

#include <stdlib.h>

extern int g_exit_status;

int	strlenvar(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*getenv_value(t_list *my_envp, char *varname)
{
	int		len_varname;
	int		len_currvar;
	char	*env_var;
	char	*ret;

	len_varname = ft_strlen(varname);
	if (ft_strcmp(varname, "?") == 0)
		return (ft_itoa(g_exit_status));
	while (my_envp)
	{
		env_var = (char *) ((t_env *) my_envp->content)->var;
		len_currvar = strlenvar(env_var);
		if (len_currvar < len_varname)
			len_currvar = len_varname;
		if (ft_strncmp(env_var, varname, len_currvar) == 0)
			return (ft_strdup(env_var + len_varname + 1));
		my_envp = my_envp->next;
	}
	ret = (char *) malloc(sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

t_env	*get_env(t_list *my_envp, char *varname)
{
	int		len_varname;
	int		len_currvar;
	char	*env_var;

	len_varname = ft_strlen(varname);
	while (my_envp)
	{
		env_var = (char *)((t_env *) my_envp->content)->var;
		len_currvar = strlenvar(env_var);
		if (len_currvar < len_varname)
			len_currvar = len_varname;
		if (ft_strncmp(env_var, varname, len_currvar) == 0)
			return ((t_env *) my_envp->content);
		my_envp = my_envp->next;
	}
	return (NULL);
}
