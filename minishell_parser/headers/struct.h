/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:34:03 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/09 10:43:43 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_lst.h"

typedef struct s_token
{
	int		code;
	char	*word;
	int		quote;
}	t_token;

typedef struct s_command
{
	t_list	*args;
	t_list	*output;
	int		append;
}	t_command;

#endif
