/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:21:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/18 17:23:32 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"

/**
 *
 */
int	ft_clone_env(t_list **envs, char *envp[]);

/**
 *
 */
int	ft_set_value(t_list *envs, const char *varname, const char *value);

/**
 *
 */
t_list	*ft_get_by_name(t_list *env, const char *varname);

#endif
