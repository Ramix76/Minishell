/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/20 18:03:41 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define METACHARACTERS	" \n\t|&;()<>\0"
#define OPERATORS		"\n|&;()<>"
#define CONTROLOP		"\n|&"
#define REDIRECTOP		"<>"

static int	simple_command(char *job, t_data *data);
int			here_doc(char *limiter);
int			read_stdin(int wr_fd, char *limiter);
int			write_output(int fd, char *output);
int			redirect_in(char *line, int *fd);

int	redirect_in(char *line, int *fd)
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
	word = ft_strndup(word, strcspn(word, METACHARACTERS));
	*fd = open(word, O_RDONLY);
	free(word);
	return (EXIT_SUCCESS);
}

int	job_control(char *line, t_data *data)
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
		cspn = strcspn(temp + 1, CONTROLOP);
		job = ft_strndup(temp, cspn + 1);
		redirect_in(job, &fd);
		if (*job == '|')
			n = strspn(job, METACHARACTERS);
		temp = strpbrk(temp + 1, CONTROLOP);
		simple_command(job + n, data);
		free(job);
	}
	return (EXIT_SUCCESS);
}

static int	simple_command(char *job, t_data *data)
{
	int		n;
	char	*temp;

	n = 0;
	temp = strpbrk(job, REDIRECTOP);
	while (temp != NULL)
	{
		if (ft_strncmp(temp, "<< ", 3) == 0)
		{
			here_doc("--");
			temp += 3;
		}
		//else if (*temp == '<')
		temp = strpbrk(temp + 1, REDIRECTOP);
	}
	printf("job is \"%s\"\n", job + n);
	command_do(job + n, data);
	return (EXIT_SUCCESS);
}

int	here_doc(char *limiter)
{
	int	fildes[2];

	pipe(fildes); //??
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

int	write_output(int fd, char *output)
{
	int		outfd;
	char	buf[1];

	outfd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	while (read(fd, buf, 1) > 0)
		write(outfd, buf, 1);
	return (0);
}

int	command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_path;

	line = shell_expand(line, data);
	cmd.tokens = ft_split(line, ' ');
	if (cmd.tokens[0] == NULL)
		return (free_str_arr(cmd.tokens), EXIT_SUCCESS);
	cmd_path = ft_which(cmd.tokens[0], data->path);
	if (is_builtin(cmd.tokens[0]) == EXIT_SUCCESS)
		builtin_do(&cmd, data);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	{
		free(line);
		free(cmd_path);
		free_str_arr(cmd.tokens);
		exit (EXIT_SUCCESS);
	}
	else if (cmd_path == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
		pipe_do(line, data);
	free(line);
	free(cmd_path);
	free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}
