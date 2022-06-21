/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:16 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/19 19:31:32 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct.h"

/**
 *
 */
int	ft_create_command(t_list **commands, t_list *tokens);

/**
 *
 */
int	ft_input(t_command *command, int code, char *str);
/**
 *
 */
int	ft_output(t_command *command, int code, char *str);

/**
 *
 */
int	ft_execute(t_list *command);

#endif
