/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:16 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/31 14:45:44 by lfrederi         ###   ########.fr       */
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
int		ft_new_command(t_command **command, int id);

/**
 *
 */
int		ft_new_redir(t_redir **redir);

/**
 *
 */
int		ft_parse_to_command(t_list **commands, t_list *tokens, int i);

/**
 *
 */
void	ft_del_redir(void *redir);

/**
 *
 */
void	ft_del_str(void	*content);

/**
 *
 */
void	ft_del_cmd(void	*command);

/**
 *
 */
int		ft_clear_cmds(t_list **commands, int ret);

/**
 *
 */
int		ft_redir(t_redir **redir, int code, char *str);

/**
 *
 */
int		ft_heredoc(t_redir *redir, char *tok_word);

/**
 *
 */
int		ft_new_node(t_list **node, void *content);

#endif
