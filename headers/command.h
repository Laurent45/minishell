/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:16 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 15:11:07 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct.h"

/**
 *
 */
int		new_command(t_command **command, int id);

/**
 *
 */
int		new_redir(t_redir **redir);

/**
 *
 */
int		parse_to_command(t_list **commands, t_list *tokens, t_list *my_envp);

/**
 *
 */
void	del_redir(void *redir);

/**
 *
 */
void	del_str(void	*content);

/**
 *
 */
void	del_cmd(void	*command);

/**
 *
 */
int		clear_cmds(t_list **commands, int ret);

/**
 *
 */
int		set_redir(t_redir **redir, int code, char *str, t_list *my_envp);

/**
 *
 */
int		set_heredoc_file(t_redir *redir, int num_cmd);

/**
 *
 */
int		heredoc(t_redir *redir, char *tok_word, t_list *my_envp);

/**
 *
 */
int		new_node(t_list **node, void *content);

#endif
