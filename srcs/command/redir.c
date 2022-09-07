/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:37:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:10:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "string.h"
#include "stdio.h"
#include "expansion.h"
#include "token.h"
#include "error.h"
#include "signal_handler.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	set_redir(t_redir **redir, int tok_code, char *tok_word, t_list *my_envp)
{
	if (new_redir(redir) == FAILED)
		return (free(tok_word), FAILED);
	if (tok_code == LESSLESS)
		return (heredoc(*redir, tok_word, my_envp));
	if (tok_code == LESS)
		(*redir)->code = INFILE;
	else if (tok_code == GREAT)
		(*redir)->code = OUTFILE;
	else if (tok_code == GREATGREAT)
		(*redir)->code = APPENDFILE;
	(*redir)->file = tok_word;
	return (SUCCESS);
}
