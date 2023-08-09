/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:17:18 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/09 11:20:43 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WR	1
#define RD	0

static int	ft_read_stdin(int wr_fd, char *limiter, t_data *data);

int	ft_here_doc(char *limiter, t_data *data)
{
	int	fildes[2];

	pipe(fildes);
	ft_read_stdin(fildes[WR], limiter, data);
	close(fildes[WR]);
	return (fildes[RD]);
}

static int	ft_read_stdin(int wr_fd, char *limiter, t_data *data)
{
	char	*line;

	write(data->out, "> ", 2);
	line = get_next_line(data->in);
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
		write(data->out, "> ", 2);
		line = get_next_line(data->in);
	}
	return (0);
}
