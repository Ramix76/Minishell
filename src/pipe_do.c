/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:29:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/19 18:24:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command(char *argv, char **envp, int *fd);

int	pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	pipe_split = ft_split(line, '|');
	while (pipe_split[i] != NULL)
	{
		if (ft_strchr(pipe_split[i], '<') != 0)
			ft_printf("redir\n");
		data->exit_code = execute_command(pipe_split[i++], data->envp, &fd);
	}
	close(fd);
	free_str_arr(pipe_split);
	return (EXIT_SUCCESS);
}

int	set_in_redirect(void)
{
	return (0);
}

static int	execute_command(char *argv, char **envp, int *fd)
{
	int			fildes[2];
	char		**cmd;
	pid_t		pid;
	int			exit_code;

	if (pipe(fildes) == -1)
		exit (4);
	pid = fork();
	if (pid == -1)
	{
		perror("pipex");
		exit(1);
	}
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
	//ft_printf("exit_code: %d\n", exit_code);
	return (exit_code);
}
