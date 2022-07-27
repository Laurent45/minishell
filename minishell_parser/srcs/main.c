/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:14:12 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 10:49:27 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "command.h"
#include "execution.h"
#include "builtins.h"
#include "struct.h"
#include "error.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "env.h"
#include "print.h"

#include <unistd.h>
#include <readline/readline.h>

t_list	*envs;

int	main(int argc, char *argv[], char *envp[])
{
	(void) argv;
	(void) argc;
	t_built	builts[NB_BUILT + 1];
	t_list *tokens = NULL;		// Content is t_token
	t_list *commands = NULL;	// Content is t_command
	char	*prompt;

	if (ft_clone_env(&envs, envp) == ENV_FAILED)
		return (-1);
	ft_init_built(builts);
	while (1)
	{
		prompt = readline("minishell $ ");
		if (!prompt)
		{
			printf("\n");
			continue ;
		}
		if (!prompt[0])
		{
			free(prompt);
			continue ;
		}
		if (ft_create_tokens(&tokens, prompt) == TOK_FAILED)
			return (-1);
		if (ft_check_tokens(&tokens) == 0)
			return (-1);
		if (ft_parse_to_command(&commands, tokens, 0) == 0)
			return (-1);
		ft_clear_tokens(&tokens, 0);
//		if (ft_lstsize(commands) == 1)
//			ft_exe_simple_cmd((t_command *) commands->content, builts);
		//else
		printf("exit = %d\n", ft_execute(&commands, builts));
		ft_clear_commands(&commands, 0);
		free(prompt);
	}
	ft_clear_env(&envs, 0);

	return (0);
}
