/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:14:33 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/31 16:09:56 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "ft_lst.h"

#include <readline/readline.h>
#include <unistd.h>

void	handler_sigint(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", UNDO_DELETE);
	printf("\033[1;31m➜  \033[0m");
	rl_redisplay();
}

void	handler_heredoc(int signum)
{
	(void) signum;
	close(0);
}
