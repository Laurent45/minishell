/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:34:03 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/21 23:27:12 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_lst.h"

typedef struct s_env
{
	char	*var;
	int		globale;
}	t_env;

typedef struct s_token
{
	int		code;
	char	*word;
	int		quote;
}	t_token;

typedef struct	s_output
{
	char	*filename;
	int		append;
}	t_output;

typedef struct	s_input
{
	int		keyboard;
	char	*filename;
	t_list	*heredoc;
}	t_input;

typedef struct s_command
{
	int				id;
	int				redirect_failed;
	t_list			*args;
	struct s_output	*output;
	struct s_input	*input;
}	t_command;

/******************************************************************************/
/*	CREATE
 ******************************************************************************/

/**
 *
 */
int		ft_new_env(t_env **env, char *var, int globale);

/**
 *
 */
int		ft_new_token(t_list **tokens, int code, char *word, int quote);

/**
 *
 */
int		ft_new_command(t_command **command);

/**
 *
 */
int		ft_new_output(t_output **output);

/**
 *
 */
int		ft_new_input(t_input **input);

/**
 *
 */
int		ft_new_node(t_list **node, void *content);

/******************************************************************************/
/*	DELETE
 ******************************************************************************/

/**
 *
 */
void	ft_del_token(void *token);

/**
 *
 */
void	ft_del_str(void	*content);

/**
 *
 */
void	ft_del_output(t_output *output);

/**
 *
 */
void	ft_del_input(t_input *input);

/**
 *
 */
void	ft_del_command(void *command);

/**
 *
 */
void	ft_del_env(void *content);

/******************************************************************************/
/*	CLEAR
 ******************************************************************************/

/**
 *
 */
int		ft_clear_tokens(t_list **tokens, int ret);

/**
 *
 */
int		ft_clear_commands(t_list **commands, int ret);

/**
 *
 */
int		ft_clear_env(t_list **env, int ret);

#endif
