/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:17:05 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 13:05:50 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

#define	RED_COLOR	"\033[1;31m"
#define	GREEN_COLOR	"\033[1;32m"
#define	CYAN_COLOR	"\033[1;36m"
#define	BOLD_TEXt	"\033[1m"
#define	END			"\033[0m"

/**
 *
 */
void	handler_sigint(int signum);

/**
 *
 */
void	handler_heredoc(int signum);

#endif
