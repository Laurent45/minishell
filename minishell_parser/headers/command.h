/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:16 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 15:45:33 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct.h"

/**
 *
 */
int	ft_new_command(t_command **command);

/**
 *
 */
int	ft_parse_to_command(t_list **commands, t_list *tokens);

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
