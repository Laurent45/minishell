/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:46:46 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 09:52:06 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "builtins.h"
# include "env.h"

/**
 *
 */
int	init_shell(char *envp[], t_list **clone_env, t_built *builts);


#endif
