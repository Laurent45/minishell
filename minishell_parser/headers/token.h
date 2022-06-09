/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:33:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/07 10:09:57 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "ft_lst.h"

# define WORD		1 
# define GREAT		2
# define LESS		3
# define GREATGREAT	4
# define LESSLESS	5
# define PIPE		6
# define S_QUOTE	7
# define D_QUOTE	8
# define ESCAPE_TAB	9


/**
 *
 */
int		ft_create_tokens(t_list **tokens, char *prompt);

/**
 *
 */
void	ft_del_token(void *token);

/**
 *
 */
int		ft_clear_tokens(t_list **tokens);

#endif
