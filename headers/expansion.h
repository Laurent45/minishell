/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:26:23 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 20:49:17 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "struct.h"

/**
 *
 */
char	*expand_trim(char *to_expand, t_list *my_envp);

/**
 *
 */
char	*expand(t_list *my_envp, char *str, int test, int i);
void	dollar_alloc2(char *tmp, char *new, char **tmp2);
/**
 *
 */
char	*trim_quote(char *str);

/**
 *
 */
int		expand_cmdargs(t_list **cmd_args, t_list *my_envp);

#endif
