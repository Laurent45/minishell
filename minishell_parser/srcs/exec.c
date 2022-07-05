/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:51:00 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 10:46:16 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>


int	main(int argc, char *argv[], char **envp)
{
	(void) argc;
	(void) argv;

	char *cmd[] = {"/bin/cat", "Makefile", NULL};
	char *cmd1[] = {"/bin/grep", "srcs", NULL};
	//char *cmd2[] = {"/bin/cat", NULL};
	//char *cmd3[] = {"/bin/rev", NULL};
	char **cmds[] = {cmd, cmd1, NULL};

	int id = fork();
	if (id == 0)
	{
		ft_exec(cmds, envp);
		return (0);
	}

	char buff[181] = {0};
	read(0, buff, 180);
	printf("%s", buff);

	return (0);
}
