/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:34:03 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 10:15:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_lst.h"

# define SUCCESS	0
# define FAILED		1

# define INFILE		1
# define OUTFILE	2
# define APPENDFILE	3
# define HEREDOC	4

typedef struct s_env
{
	char	*var;
	int		globale;
}	t_env;

typedef struct s_built
{
	char	*func;
	int		(*f)(t_list *args);
}	t_built;

typedef struct s_token
{
	int		code;
	char	*str;
}	t_token;

typedef struct s_redir
{
	int		code;
	char	*file;
	t_list	*heredoc;
}	t_redir;

typedef struct s_command
{
	int				pid;
	int				num;
	t_list			*cmd_args;
	t_list			*redir;
	t_list			*env_var;
}	t_command;

#endif
