/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:22:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 14:51:29 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "struct.h"

/**
 *
 */
int		exe_pipeline(t_list **commands, t_built *builts, t_list **my_envp);

/**
 *
 */
int		exe_simple_cmd(t_list **commands, t_built *builts, t_list **my_envp);

/**
 *
 */
int		wait_child(t_list *command);

/**
 *
 */
int		redirection(t_command *cmd, t_list *my_envp);

/**
 *
 */
int		assignement(t_list **my_envp, t_list *var, int globale);

/**
 *
 */
int		search_exe(t_list *cmd, t_list *my_envp);

/**
 *
 */
int		run_executable(t_command *command, t_list **my_envp);

/**
 *
 */
int		child_std(t_list *node_cmd, int pipe[2], int tmpin);

/**
 *
 */
void	child_pipeline(t_list **commands, t_command *cmd, t_built *builts\
		, t_list **my_envp);
/**
 *
 */
void	child_simple_cmd(t_list **commands, t_list **my_envp);

/**
 *
 */
void	exit_clear(t_list **commands, t_list **my_envp, int ret);

#endif
