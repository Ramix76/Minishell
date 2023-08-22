/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:17:18 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/22 15:52:56 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WR	1
#define RD	0

static int	ft_read_stdin(int fd_wr, char *limiter, t_data *data);

int	ft_here_doc(char *limiter, t_data *data)
{
	int		fildes[2];
	pid_t	pid;
	int		status;

	if (isatty(data->fd_in) != 0)
		dup2(data->fd_in, STDIN_FILENO);
	status = 0;
	if (pipe(fildes) == -1)
		return (EXIT_FAILURE);
	ft_init_signals(3);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		ft_init_signals(2);
		close(fildes[RD]);
		ft_read_stdin(fildes[WR], limiter, data);
		exit(g_exit_code);
	}
	if (waitpid(pid, &status, 0) && WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	close(fildes[WR]);
	data->in = fildes[RD];
	return (EXIT_SUCCESS);
}

static int	ft_read_stdin(int fd_wr, char *limiter, t_data *data)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_wr);
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	return (EXIT_SUCCESS);
	(void) data;
}
