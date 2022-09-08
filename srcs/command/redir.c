/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:37:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 14:40:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "ft_string.h"
#include "token.h"

#include <stdlib.h>

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

int	set_heredoc_file(t_redir *redir, int num_cmd)
{
	char	*num;
	char	*file_heredoc;

	num = ft_itoa(num_cmd);
	if (!num)
		return (FAILED);
	file_heredoc = ft_strjoin(TMP_FILE, num);
	free(num);
	if (!file_heredoc)
		return (FAILED);
	redir->file_heredoc = file_heredoc;
	return (SUCCESS);
}
