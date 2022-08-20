/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:26:23 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/31 16:14:02 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "struct.h"

/**
 *
 */
char	*ft_expand_trim(char *to_expand);

/**
 *
 */
char	*ft_expand(char *str, int test, int i);

/**
 *
 */
char	*ft_trim_quote(char *str);

/**
 *
 */
int		ft_expand_cmdargs(t_list **cmd_args);

#endif
