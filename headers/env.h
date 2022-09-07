/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:21:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 21:09:20 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"

/**
 *
 */
int		clone_env(t_list **my_envp, char *envp[]);

/**
 *
 */
int		new_env(t_env **env, char *var, int globale);

/**
 *
 */
int		add_envvar(t_list **my_envp, char *envvar, int globale);

/**
 *
 */
void	add_existatus(int exitstatus);

/**
 *
 */
char	*getenv_value(t_list *my_envp, char *varname);

/**
 *
 */
t_env	*get_env(t_list *my_envp, char *varname);

/**
 *
 */
int		strlenvar(char *var);

/**
 *
 */
void	del_env(void	*content);

/**
 *
 */
int		clear_env(t_list **env, int ret);

#endif
