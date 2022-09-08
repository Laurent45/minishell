/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:14:12 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 15:14:18 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "command.h"
#include "execution.h"
#include "builtins.h"
#include "error.h"
#include "signal_handler.h"
#include "init.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>

int	g_exit_status;

static int	run_shell(char *prompt, t_built *builts, t_list **my_envp)
{
	t_list	*tokens;
	t_list	*commands;

	tokens = NULL;
	commands = NULL;
	if (create_tokens(&tokens, prompt, 0) == FAILED)
		return (free(prompt), FAILED);
	free(prompt);
	if (!tokens)
		return (SUCCESS);
	if (check_tokens(&tokens) == FAILED)
		return (clear_tokens(&tokens, FAILED));
	if (parse_to_command(&commands, tokens, *my_envp) == FAILED)
		return (clear_tokens(&tokens, FAILED));
	clear_tokens(&tokens, 0);
	if (ft_lstsize(commands) == 1)
	{
		if (exe_simple_cmd(&commands, builts, my_envp) == EXIT_BUILT)
			return (clear_cmds(&commands, EXIT_BUILT));
	}
	else
		exe_pipeline(&commands, builts, my_envp);
	return (clear_cmds(&commands, SUCCESS));
}

static int	get_prompt(char **prompt)
{
	signal(SIGINT, &handler_sigint);
	if (g_exit_status == 0)
		printf(GREEN_ARROW);
	else
		printf(RED_ARROW);
	*prompt = readline(PROMPT);
	signal(SIGINT, SIG_IGN);
	if (!*prompt)
		return (printf("exit\n"), 2);
	if (!*prompt[0])
		return (free(*prompt), 1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*my_envp;
	t_built	builts[NB_BUILT + 1];
	char	*prompt;
	int		ret_prompt;

	(void) argv;
	(void) argc;
	signal(SIGQUIT, SIG_IGN);
	if (init_shell(envp, &my_envp, builts) == FAILED)
		return (-1);
	while (1)
	{
		ret_prompt = get_prompt(&prompt);
		if (ret_prompt == 1)
			continue ;
		if (ret_prompt == 2)
			break ;
		add_history(prompt);
		if (run_shell(prompt, builts, &my_envp) == EXIT_BUILT)
			break ;
	}
	rl_clear_history();
	return (clear_env(&my_envp, g_exit_status));
}
