/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:16 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/15 15:18:05 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct.h"

# define CMD_SUCCESS	1
# define CMD_FAILED		0

/**
 *
 */
int	ft_new_command(t_command **command, int id);

/**
 *
 */
int	ft_parse_to_command(t_list **commands, t_list *tokens, int i);

/**
 *
 */
void	ft_del_redir(void *redir);

/**
 *
 */
void	ft_del_command(void	*command);
/**
 *
 */
int		ft_clear_commands(t_list **commands, int ret);

/**
 *
 */
int	ft_new_redir(t_redir **redir, int code, char *str);

/**
 *
 */
int	ft_new_node(t_list **node, void *content);

#endif
