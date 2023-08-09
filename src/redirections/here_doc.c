/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:17:18 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/09 16:44:09 by framos-p         ###   ########.fr       */
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

	g_in_heredoc = 1;
	if (pipe(fildes) == -1)
		return (EXIT_FAILURE);
	ft_init_signals(2, data);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		ft_init_signals(0, data);
		close(fildes[RD]);
		ft_read_stdin(fildes[WR], limiter, data);
		exit (0);
	}
	waitpid(pid, NULL, 0);
	close(fildes[WR]);
	data->in = fildes[RD];
	g_in_heredoc = 0;
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
