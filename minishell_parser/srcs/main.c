/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:14:12 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/26 18:12:28 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "command.h"
#include "struct.h"
#include "error.h"
#include <stddef.h>
#include <stdio.h>

#include "env.h"
#include "print.h"

t_list	*envs;

/*int	main(int argc, char *argv[], char *envp[])
{
	if (argc == 1)
		return (0);

	t_list *tokens = NULL;		// Content is t_token
	t_list *commands = NULL;	// Content is t_command
	envs = NULL;				// Content is t_env

	if (ft_clone_env(&envs, envp) == 0)
		return (-1);
	if (ft_create_tokens(&tokens, argv[1]) == 0)
		return (-1);

	if (ft_check_tokens(&tokens) == 0)
		return (-1);

	if (ft_create_command(&commands, tokens) == 0)
		return (-1);
	print_tokens(tokens);
	ft_clear_tokens(&tokens, 0);
	print_command(commands);
//	ft_execute(commands);
//	ft_clear_commands(&commands, 0);
	ft_clear_env(&envs, 0);
	return (0);
}*/

int	main()
{
	char	*line;
	t_list	*node;

	write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
		return (ft_allocated_err(0, "get_next_line"));
	while (line)
	{
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
		{
			free(line);
			return (1);
		}
		if (ft_new_node(&node, line) == 0)
		{
			free(line);
			return (ft_allocated_err(0, "node in ft_heredoc"));
		}
		ft_lstadd_back(&(command->input->heredoc), node);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	return (0);
}
