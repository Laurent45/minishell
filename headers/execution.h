/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:22:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/26 19:25:17 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "struct.h"

# define EXPAND_FAILED	1
# define REDIR_FAILED	2	

/**
 *
 */
int		ft_execute(t_list **commands, t_built *builts);

/**
 *
 */
int		ft_wait_child(t_list *command);

/**
 *
 */
int		ft_redirection(t_command *cmd);

/**
 *
 */
int		ft_assignement(t_list *var, int globale);

/**
 *
 */
int		ft_search_exe(t_list *cmd);

/**
 *
 */
int		ft_run_executable(t_command *command);

/**
 *
 */
void	ft_child_std(t_list **cmds, t_list *node_cmd, int pipe[2], int tmpin);

/**
 *
 */
void	ft_child_pipeline(t_list **commands, t_command *cmd, t_built *builts);

/**
 *
 */
void	ft_child_simple_cmd(t_list **commands);

#endif
