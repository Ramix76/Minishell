/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:29:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/15 16:21:16 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipex(char **argv, t_data *data);
static void	execute_command(char *argv, char **envp, int *fd);

int	pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	int		i;

	pipe_split = ft_split(line, '|');
	pipex(pipe_split, data);
	i = 0;
	while (pipe_split[i] != NULL)
		free(pipe_split[i++]);
	free(pipe_split);
	return (EXIT_SUCCESS);
}

static int	pipex(char **argv, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = STDIN_FILENO;
	while (argv[i] != NULL)
	{
		//dup2(fd, STDIN_FILENO);
		//close(fd);
		execute_command(argv[i], data->envp, &fd);
		++i;
	}
	//close(fd);
	return (EXIT_SUCCESS);
}

static void	execute_command(char *argv, char **envp, int *fd)
{
	int		fildes[2];
	char	**cmd;
	pid_t	pid;

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
		exit (1);
	}
	waitpid(pid, NULL, 0);
	//close(fildes[WR]);
	//*fd = fildes[RD];
	(void) fd;
}
