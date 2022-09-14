/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:46:46 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 21:51:22 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "builtins.h"
# include "env.h"

# define GREEN_ARROW	"\033[1;32m➜  \033[0m"
# define RED_ARROW		"\033[1;31m➜  \033[0m"
# define PROMPT			"\002\033[1;36m\003minishell\002\033[0m\003 $ "

/**
 *
 */
int		init_shell(char *envp[], t_list **clone_env, t_built *builts);

/**
 *
 */
void	set_status(int status);

/**
 *
 */
int		get_status(void);

#endif
