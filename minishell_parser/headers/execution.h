/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:22:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 16:03:52 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "struct.h"

/**
 *
 */
int	ft_set_stream(t_list **commands, int pid, int pipe[2], t_list *node_command);

/**
 *
 */
int	ft_execute(t_list **commands);

/**
 *
 */
void ft_exit(t_list **command, char **envp, char **args, int ret);

#endif
