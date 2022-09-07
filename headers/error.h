/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:15:56 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 10:37:13 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SYNTAX_ERROR "minishell: syntax error"

/**
 *	Use perror function for print an error message with type given in parameter.
 *	Return the value ret;
 */
int	allocated_err(int ret, const char *type);

/**
 *
 */
int	puterror(int ret, char *message);

/**
 *
 */
int	ft_perror(int ret, char *message);

#endif
