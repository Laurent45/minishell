/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:21:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/26 19:23:26 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"

# define ENV_FAILED			-1
# define ENV_SUCCESS		0
# define ASSIGNEMENT_FAILED	1

/**
 *
 */
int		ft_clone_env(t_list **envs, char *envp[]);

/**
 *
 */
int		ft_new_env(t_env **env, char *var, int globale);

/**
 *
 */
int		ft_add_envvar(char *envvar, int globale);

/**
 *
 */
char	*ft_getenv_value(char *varname);

/**
 *
 */
t_env	*ft_getenv(char *varname);

/**
 *
 */
int		ft_strlenvar(char *var);

/**
 *
 */
void	ft_del_env(void	*content);

/**
 *
 */
int		ft_clear_env(t_list **env, int ret);

#endif
