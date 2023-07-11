/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 12:59:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define METACHARACTERS	" \n\t|&;()<>\0"
#define OPERATORS		"\n|&;()<>"
#define CONTROLOP		"\n|&"
#define REDIRECTOP		"<>"

static int	ft_simple_command(char *job, t_data *data);
int			ft_here_doc(char *limiter);
int			ft_read_stdin(int wr_fd, char *limiter);
int			ft_write_output(int fd, char *output);
int			ft_redirect_in(char *line, int *fd);
static int	ft_execute_command(char *argv, char **envp, int *fd);

int	ft_redirect_in(char *line, int *fd)
{
	char	*temp;
	char	*word;

	temp = line;
	while (temp != NULL)
	{
		word = temp;
		temp = ft_strchr(temp + 1, '<');
	}
	if (word == NULL)
		return (EXIT_FAILURE);
	++word;
	while (word != NULL && *word != '\0' && ft_isspace(*word) != 0)
		++word;
	word = ft_strndup(word, ft_strcspn(word, METACHARACTERS));
	*fd = open(word, O_RDONLY);
	free(word);
	return (EXIT_SUCCESS);
}

int	ft_job_control(char *line, t_data *data)
{
	int		n;
	int		fd;
	char	*temp;
	char	*job;
	size_t	cspn;

	temp = line;
	fd = STDIN_FILENO;
	while (temp != NULL)
	{
		n = 0;
		cspn = ft_strcspn(temp + 1, CONTROLOP);
		job = ft_strndup(temp, cspn + 1);
		ft_redirect_in(job, &fd);
		if (*job == '|')
			n = ft_strspn(job, METACHARACTERS);
		temp = ft_strpbrk(temp + 1, CONTROLOP);
		ft_simple_command(job + n, data);
		free(job);
	}
	return (EXIT_SUCCESS);
}

static int	ft_simple_command(char *job, t_data *data)
{
	int		n;
	char	*temp;

	n = 0;
	temp = ft_strpbrk(job, REDIRECTOP);
	while (temp != NULL)
	{
		if (ft_strncmp(temp, "<< ", 3) == 0)
		{
			ft_here_doc("--");
			temp += 3;
		}
		//else if (*temp == '<')
		temp = ft_strpbrk(temp + 1, REDIRECTOP);
	}
	//printf("job is \"%s\"\n", job + n);
	ft_command_do(job + n, data);
	return (EXIT_SUCCESS);
}

int	ft_here_doc(char *limiter)
{
	int	fildes[2];

	pipe(fildes); //??
	ft_read_stdin(fildes[WR], limiter);
	close(fildes[WR]);
	return (fildes[RD]);
}

int	ft_read_stdin(int wr_fd, char *limiter)
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

int	ft_write_output(int fd, char *output)
{
	int		outfd;
	char	buf[1];

	outfd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	while (read(fd, buf, 1) > 0)
		write(outfd, buf, 1);
	return (0);
}

int	ft_command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_path;

	line = ft_shell_expand(line, data);
	cmd.tokens = ft_split(line, ' ');
	if (cmd.tokens[0] == NULL)
		return (ft_free_str_arr(cmd.tokens), EXIT_SUCCESS);
	cmd_path = ft_which(cmd.tokens[0], data->path);
	if (ft_is_builtin(cmd.tokens[0]) == EXIT_SUCCESS)
		ft_builtin_do(&cmd, data);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	{
		free(line);
		free(cmd_path);
		ft_free_str_arr(cmd.tokens);
		exit (EXIT_SUCCESS);
	}
	else if (cmd_path == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
		ft_pipe_do(line, data);
	free(line);
	free(cmd_path);
	ft_free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}

int	ft_pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	pipe_split = ft_split(line, '|');
	while (pipe_split[i] != NULL)
	{
		//if (ft_strchr(pipe_split[i], '<') != 0)
		//	ft_printf("redir\n");
		data->exit_code = ft_execute_command(pipe_split[i++], data->envp, &fd);
	}
	close(fd);
	ft_free_str_arr(pipe_split);
	return (EXIT_SUCCESS);
}

static int	ft_execute_command(char *argv, char **envp, int *fd)
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
