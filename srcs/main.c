/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:14:12 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/06 15:25:06 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "command.h"
#include "execution.h"
#include "builtins.h"
#include "error.h"
#include "env.h"
#include "signal_handler.h"
#include "ft_string.h"

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

t_list	*g_envs;

static int	ft_run_shell(char *prompt, t_built *builts)
{
	t_list	*tokens;
	t_list	*commands;
	int		exitstatus;

	tokens = NULL;
	commands = NULL;
	if (ft_create_tokens(&tokens, prompt, 0) == 0)
		return (free(prompt), 0);
	free(prompt);
	if (!tokens)
		return (0);
	if (ft_check_tokens(&tokens) != 1)
		return (ft_clear_tokens(&tokens, 0));
	if (ft_parse_to_command(&commands, tokens, 0) == 0)
		return (ft_clear_tokens(&tokens, 0));
	ft_clear_tokens(&tokens, 0);
	exitstatus = ft_execute(&commands, builts);
	if (exitstatus == EXIT_BUILT && ft_lstsize(commands) == 1)
		return (ft_clear_cmds(&commands, 1));
	ft_add_existatus(exitstatus);
	return (ft_clear_cmds(&commands, 0));
}

static int	ft_get_prompt(char **prompt)
{
	char	*status;

	status = ft_getenv_value("?");
	signal(SIGINT, &handler_sigint);
	if (ft_atoi(status) == 0)
		printf("\033[1;32m➜  \033[0m");
	else
		printf("\033[1;31m➜  \033[0m");
	free(status);
	*prompt = readline("\002\033[1;36m\003minishell\002\033[0m\003 $ ");
	signal(SIGINT, SIG_IGN);
	if (!*prompt)
		return (printf("exit\n"), 2);
	if (!*prompt[0])
		return (free(*prompt), 1);
	return (0);
}

static int	ft_return_status(void)
{
	char	*status;
	int		ret;

	status = ft_getenv_value("?");
	ret = ft_atoi(status);
	free(status);
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_built	builts[NB_BUILT + 1];
	char	*prompt;
	int		exit;
	int		ret_prompt;

	(void) argv;
	(void) argc;
	signal(SIGQUIT, SIG_IGN);
	if (ft_clone_env(&g_envs, envp) == ENV_FAILED)
		return (-1);
	ft_init_built(builts);
	exit = 0;
	while (1 && exit == 0)
	{
		ret_prompt = ft_get_prompt(&prompt);
		if (ret_prompt == 1)
			continue ;
		if (ret_prompt == 2)
			break ;
		add_history(prompt);
		exit = ft_run_shell(prompt, builts);
	}
	rl_clear_history();
	return (ft_clear_env(&g_envs, ft_return_status()));
}
