/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:19:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 16:22:04 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_command(char *argv, char **envp, int *fd)
{
	int			fildes[2];
	char		**cmd;
	pid_t		pid;
	int			exit_code;

	if (pipe(fildes) == -1)
		exit(4);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		cmd = ft_split(argv, ' ');
		//dup2(fildes[WR], STDOUT_FILENO);
		//close(fildes[RD]);
		//close(fildes[WR]);
		ft_execvpe(cmd[0], (char const **) cmd, (const char **) envp);
		exit (EXIT_FAILURE);
	}
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		exit_code = WEXITSTATUS(exit_code);
	close(fildes[WR]);
	*fd = fildes[RD];
	return (exit_code);
}
