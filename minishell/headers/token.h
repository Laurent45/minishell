/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:33:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/20 23:32:54 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "struct.h"

# define TOK_FAILED		-1
# define TOK_SUCCESS	0
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

# define ESCAPE_TAB	9
# define NOT_META	10

/**
 *
 */
int		ft_create_tokens(t_list **tokens, char *prompt, int i);

/**
 *
 */
int		ft_check_tokens(t_list **tokens);

/**
 *
 */
int		ft_new_token(t_list **tokens, int code, char *word);

/**
 *
 */
int		ft_new_token(t_list **tokens, int code, char *word);

/**
 *
 */
int		unquote_case(char **arg, t_list **tokens, char **buff, int *state);

/**
 *
 */
void	ft_del(void *token);

/**
 *
 */
int		ft_clear_tokens(t_list **tokens, int ret);

/**
 *
 */
int	meta_alloc(int code, int *state, char **arg, t_list **tokens);

//UTILS
/**
 *
 */
int		is_alphanum(char c);

/**
 *
 */
int		is_meta(char c);

/**
 *
 */
int		is_it(char c);

int	quote_case(char **arg, t_list **tokens, char **buff, int *state);
int	quote_detect(char *str, int *code);
int	buff_alloc(char **arg, char **buff, int *i);
int	tok_alloc_err(t_list **tokens);
int	lst_alloc(char **arg, char **buff, t_list **tokens);

#endif
