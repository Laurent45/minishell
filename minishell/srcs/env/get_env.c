/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:00:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 16:52:25 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"

#include <stdlib.h>

extern t_list	*g_envs;

int	ft_strlenvar(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*ft_getenv_value(char *varname)
{
	t_list	*envs;
	int		len_varname;
	int		len_currvar;
	char	*env_var;
	char	*ret;

	envs = g_envs;
	len_varname = ft_strlen(varname);
	while (envs)
	{
		env_var = (char *)((t_env *) envs->content)->var;
		len_currvar = ft_strlenvar(env_var);
		if (len_currvar < len_varname)
			len_currvar = len_varname;
		if (ft_strncmp(env_var, varname, len_currvar) == 0)
			return (ft_strdup(env_var + len_varname + 1));
		envs = envs->next;
	}
	ret = (char *) malloc(sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

t_env	*ft_getenv(char *varname)
{
	t_list	*envs;
	int		len_varname;
	int		len_currvar;
	char	*env_var;

	envs = g_envs;
	len_varname = ft_strlen(varname);
	while (envs)
	{
		env_var = (char *)((t_env *) envs->content)->var;
		len_currvar = ft_strlenvar(env_var);
		if (len_currvar < len_varname)
			len_currvar = len_varname;
		if (ft_strncmp(env_var, varname, len_currvar) == 0)
			return ((t_env *) envs->content);
		envs = envs->next;
	}
	return (NULL);
}
