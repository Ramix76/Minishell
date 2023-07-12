/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:17:18 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 16:18:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(char *limiter)
{
	int	fildes[2];

	pipe(fildes);
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
