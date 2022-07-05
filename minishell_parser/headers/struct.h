/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:34:03 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 14:49:08 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_lst.h"

# define INFILE		1
# define OUTFILE	2
# define APPENDFILE	3
# define HEREDOC	4


typedef struct s_env
{
	char	*var;
	int		globale;
}	t_env;

typedef struct s_token
{
	int		code;
	char	*word;
}	t_token;

typedef struct	s_redir
{
	int		code;
	char	*file;
	t_list	*heredoc;	// Content is char *
}	t_redir;

typedef struct s_command
{
	int				id;
	t_list			*cmd_args;		// Content is char *
	t_list			*redir;		// Content is t_redir
	t_list			*env_var;	// Content is char *
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

/**
 *
 */

/**
 *
 */
//int		ft_new_output(t_output **output);

/**
 *
 */
//int		ft_new_input(t_input **input);

/**
 *
 */

/**
 *
 */

/******************************************************************************/
/*	DELETE
 ******************************************************************************/

/**
 *
 */

/**
 *
 */
void	ft_del_str(void	*content);

/**
 *
 */
//void	ft_del_output(t_output *output);

/**
 *
 */
//void	ft_del_input(t_input *input);

/**
 *
 */

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

/**
 *
 */

/**
 *
 */
int		ft_clear_env(t_list **env, int ret);

#endif
