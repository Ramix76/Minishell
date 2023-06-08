/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:01:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 19:08:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

# define WR 1
# define RD	0

static int	pipe_do(char *line, t_data *data);
static int	pipex(int argc, char **argv, t_data *data);
static void	execute_command(char *argv, char **envp, int *fd);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	init_log(argc, argv, envp);
	line = "cat infile | cat -n";
	pipe_do(line, &data);
	return (0);
}

static int	pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	char	*str;
	int		i;

	pipe_split = ft_split(line, '|');
	i = 0;
	while (pipe_split[i] != NULL)
	{
		str = ft_strtrim(pipe_split[i], " ");
		free(pipe_split[i]);
		pipe_split[i] = str;
		++i;
	}
	pipex(i, pipe_split, data);
	i = 0;
	while (pipe_split[i] != NULL)
		free(pipe_split[i++]);
	free(pipe_split);
	return (EXIT_SUCCESS);
}

static int	pipex(int argc, char **argv, t_data *data)
{
	int	i;
	int	fd;

	(void) argc;
	(void) argv;
	(void) data;
	i = 0;
	fd = STDIN_FILENO;
	while (i < argc)
	{
		ft_printf("Will execute %s\n", argv[i]);
		dup2(fd, STDIN_FILENO);
		close(fd);
		execute_command(argv[i], data->envp, &fd);
		++i;
	}
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
		dup2(fildes[WR], STDOUT_FILENO);
		close(fildes[RD]);
		close(fildes[WR]);
		ft_execvpe(cmd[0], (char const **) cmd, (const char **) envp);
		exit (1);
	}
	waitpid(pid, NULL, 0);
	close(fildes[WR]);
	*fd = fildes[RD];
}
