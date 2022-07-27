/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:26:23 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 10:51:34 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "struct.h"

typedef enum e_token_kind
{
	WORD = 1,
	DOLLAR,
	D_QUOTE,
	S_QUOTE,
	LESS,
	GREAT,
	LESSLESS,
	GREATGREAT,
	PIPE,
}	t_token_kind;

/**
 *
 */
char	*mini_expand(char *str, int test, int i);

/**
 *
 */
char	*trim_quote(char *str);

int	is_alphanum(char c);

int	is_meta(char c);

int	is_it(char c);

int	is_num(char c);

int	ft_expand_cmdargs(t_list **cmd_args);

#endif
