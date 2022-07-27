/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:22:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 11:00:44 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "struct.h"

/**
 *
 */
int		ft_execute(t_list **commands, t_built *builts);

/**
 *
 */
void	ft_child(t_list **commands, t_list *node_cmd, int pipe[2], int tmpin);

/**
 *
 */
void	ft_exit(t_list **command, char **envp, char **args, int ret);

/**
 *
 */
int		ft_execute_failed(t_list *node_command, char *func, int ret);

int		ft_redirection(t_command *cmd);

void		ft_simple_cmd(t_list **command);

void	ft_run_exe(t_list **commands, t_command *cmd, t_built *builts);

char **ft_args_to_array(t_list *lst);

char **ft_envs_to_array(t_list *lst);

int	ft_search_exe(t_list *cmd);

#endif
