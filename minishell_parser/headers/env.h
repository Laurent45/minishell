/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:21:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/17 16:46:35 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"

# define ENV_FAILED		-1
# define ENV_SUCCESS	0

/**
 *
 */
int	ft_clone_env(t_list **envs, char *envp[]);

/**
 *
 */
int	ft_set_value(const char *varname, const char *value);

/**
 *
 */
int	ft_get_envvar(char *varname, char **value);

#endif
