/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:14:49 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 15:28:40 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

# define NB_BUILT	7
# define EXIT_BUILT	3

/**
 *
 */
t_built	*isbuiltins(t_list *cmd_args, t_built *builts);

/**
 *
 */
int		run_builtins(t_built *built, t_command *command, t_list **my_envp);

/**
 *
 */
int		built_cd(t_list *args, t_list **my_envp);

/**
 *
 */
int		built_echo(t_list *args, t_list **my_envp);


/**
 *
 */
int		built_env(t_list *args, t_list **my_envp);


/**
 *
 */
int		built_exit(t_list *args, t_list **my_envp);


/**
 *
 */
int		built_export(t_list *args, t_list **my_envp);


/**
 *
 */
int		built_pwd(t_list *args, t_list **my_envp);


/*
 *
 */
int		built_unset(t_list *args, t_list **my_envp);


#endif
