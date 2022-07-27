/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:21:03 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/19 19:27:42 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "struct.h"

void	print_tokens(t_list *tokens);
void	print_strings(t_list *strings);
void	print_args(t_list *strings);
void	print_command(t_list *commands);
void	print_env(t_list *envs);

#endif
