/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:22:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/22 21:30:44 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "struct.h"

/**
 *
 */
int	 ft_init_stream(int fd_saved[2]);

/**
 *
 */
int	ft_saved_std(int std_saved[2]);

/**
 *
 */
int	ft_set_input(t_command *cmd, int fdin);

/**
 *
 */
int	ft_set_output(t_list *command, int fd_in_out[2], int tmpout);

/**
 *
 */
void ft_exit(t_list *command, char **envp, char **args, int ret);

#endif
