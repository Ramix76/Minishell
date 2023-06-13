/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:01:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/13 20:47:09 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

#define WR 1
#define RD	0

static int	pipe_do(char *line, t_data *data);
static int	pipex(int argc, char **argv, t_data *data);
static void	execute_command(char *argv, char **envp, int *fd);

int			here_doc(char *limiter);
int			read_stdin(int wr_fd, char *limiter);
int			write_output_fd(char *output, int fd);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	init_log(argc, argv, envp);
	line = "cat infile | cat -n > outfile";
	//line = "command -v brew | echo hola";
	pipe_do(line, &data);
	return (0);
}

static int	pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	char	*str;
	int		i;

	if (ft_strnstr(line, " || ", ft_strlen(line)) != 0)
		ft_printf("found ||\n");
	else if (ft_strnstr(line, " && ", ft_strlen(line)) != 0)
		ft_printf("found &&\n", ft_strlen(line));
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

/* imported from pipex */
int	here_doc(char *limiter)
{
	int	fildes[2];

	pipe(fildes);
	read_stdin(fildes[WR], limiter);
	close(fildes[WR]);
	return (fildes[RD]);
}

int	read_stdin(int wr_fd, char *limiter)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (*line == *limiter
			&& ft_strncmp(limiter, line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, wr_fd);
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	return (0);
}

int	write_output_fd(char *output, int fd)
{
	int		outfd;
	char	buf[1];

	outfd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	while (read(fd, buf, 1) > 0)
		write(outfd, buf, 1);
	return (0);
}
